#include "pch.h"
#include "GameManager.h"
#include "Player.h"

GameManager::GameManager() : m_WhitePlayer(sf::Color::White), m_BlackPlayer(sf::Color::Black)
{
	m_Window.create(sf::VideoMode(700, 700), "Chess", sf::Style::Default);
}

void GameManager::addGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void GameManager::removeGameObject(GameObject* gameObject)
{
	std::vector<GameObject*>::iterator it;
	it = m_GameObjects.begin();
	while (it != m_GameObjects.end())
	{
		if (*it == gameObject)
		{
			m_GameObjects.erase(it);
			break;
		}

		for (auto container : m_GameObjectContainers)
			container->removeGameObject(gameObject);

		++it;
	}
}

void GameManager::readInput()
{
	while (m_Window.pollEvent(m_Event))
	{
		switch (m_Event.type)
		{
			case sf::Event::Closed:
			{
				m_Window.close();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (m_WhitePlayer.isPlayerTurn())
				{
					if (m_WhitePlayer.pieceIsChosen())
						m_Board.chooseSquareForPiece(sf::Mouse::getPosition(m_Window));
					else
						m_WhitePlayer.choosePiece(sf::Mouse::getPosition(m_Window));

					if (m_Board.squareIsChosen())
					{
						if (m_WhitePlayer.isLegalMove(*m_Board.getFocusedSquare()))
						{
							m_WhitePlayer.makeMove(*m_Board.getFocusedSquare());
							m_Board.resetFocusedSquare();
							m_WhitePlayer.endTurn();
							m_BlackPlayer.startTurn();
						}
						else
						{
							//Reset the focused piece
							m_WhitePlayer.resetFocusedPiece();

							//Reset the color of the square with selected piece
							//TO DO
						}
					}
				}
				else
				{
					if (m_BlackPlayer.isPlayerTurn())
					{
						if (m_BlackPlayer.pieceIsChosen())
							m_Board.chooseSquareForPiece(sf::Mouse::getPosition(m_Window));
						else
							m_BlackPlayer.choosePiece(sf::Mouse::getPosition(m_Window));

						if (m_Board.squareIsChosen())
						{
							if (m_BlackPlayer.isLegalMove(*m_Board.getFocusedSquare()))
							{
								m_BlackPlayer.makeMove(*m_Board.getFocusedSquare());
								m_Board.resetFocusedSquare();
								m_BlackPlayer.endTurn();
								m_WhitePlayer.startTurn();
							}
							else
							{
								//Reset the focused piece
								m_BlackPlayer.resetFocusedPiece();

								//Reset the color of the square with selected piece
								//TO DO
							}
						}
					}
				}
			}
		}
	}
}

void GameManager::update()
{

}

void GameManager::draw()
{
	m_Window.clear();
	
	for (auto& gameObject : m_GameObjects)
		m_Window.draw(*gameObject);

	m_Window.display();
}

void GameManager::runGame()
{
	//m_GameObjectContainers.push_back(&m_Board);
	m_GameObjectContainers.push_back(&m_WhitePlayer);
	m_GameObjectContainers.push_back(&m_BlackPlayer);

	m_Board.loadBoard(m_Window);
	m_Board.registerGameObjects();
	m_Board.assignPiecesToPlayers(m_WhitePlayer, m_BlackPlayer);
	m_WhitePlayer.registerGameObjects();
	m_BlackPlayer.registerGameObjects();

	while (m_Window.isOpen())
	{
		readInput();
		update();
		draw();
	}
}

GameManager& GameManager::getInstance()
{
	static GameManager gameManager;
	return gameManager;
}

GameManager::~GameManager()
{
}
