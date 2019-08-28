#include "pch.h"
#include "GameManager.h"
#include "Player.h"

GameManager::GameManager() : 
m_WhitePlayer(sf::Color::White),
m_BlackPlayer(sf::Color::Black),
m_ChessLogic(&m_Board, &m_WhitePlayer, &m_BlackPlayer)

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

void GameManager::addGameObjectContainer(GameObjectContainer* collection)
{
	m_GameObjectContainers.push_back(collection);
}

void GameManager::removeGameObjectContainer(GameObjectContainer* collection)
{
	std::vector<GameObjectContainer*>::iterator it;
	it = m_GameObjectContainers.begin();
	while (it != m_GameObjectContainers.end())
	{
		if (*it == collection)
		{
			m_GameObjectContainers.erase(it);
			break;
		}
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
				m_ChessLogic.onClick(m_Window);
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
	//m_GameObjectContainers.push_back(&m_Board); OLD DESIGN

	//Add players to the array of game object containers
	m_GameObjectContainers.push_back(&m_WhitePlayer);
	m_GameObjectContainers.push_back(&m_BlackPlayer);

	//Load the board
	m_Board.loadBoard(m_Window);
	m_Board.assignPiecesToPlayers(m_WhitePlayer, m_BlackPlayer);

	//Resize the pieces according to the size of square
	m_WhitePlayer.resizePieces(m_Board.getSquareSize());
	m_BlackPlayer.resizePieces(m_Board.getSquareSize());

	//Register the game objects
	m_Board.registerGameObjects();
	m_WhitePlayer.registerGameObjects();
	m_BlackPlayer.registerGameObjects();

	//Game loop
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
