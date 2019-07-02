#include "pch.h"
#include "ChessGame.h"

ChessGame::ChessGame()
{
	m_Window.create(sf::VideoMode(700, 700), "Chess", sf::Style::Default);
}

void ChessGame::addGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void ChessGame::addDrawableObject(sf::Drawable* drawableObject)
{
	m_DrawableObjects.push_back(drawableObject);
}

void ChessGame::removeGameObject(GameObject* gameObject)
{
	std::vector<GameObject*>::iterator it;
	it = m_GameObjects.begin();
	while (it != m_GameObjects.end())
	{
		if (*it == gameObject)
			m_GameObjects.erase(it);
		++it;
	}
}

void ChessGame::removeDrawableObject(sf::Drawable* drawableObject)
{
	std::vector<sf::Drawable*>::iterator it;
	it = m_DrawableObjects.begin();
	while (it != m_DrawableObjects.end())
	{
		if (*it == drawableObject)
		{
			m_DrawableObjects.erase(it);
			break;
		}
		++it;
	}
}

void ChessGame::readInput()
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
				m_Board.readInput(sf::Mouse::getPosition(m_Window));
			}
		}
	}
}

void ChessGame::update()
{

}

void ChessGame::draw()
{
	m_Window.clear();
	
	for (auto& drawableObject : m_DrawableObjects)
		m_Window.draw(*drawableObject);

	m_Window.display();
}

void ChessGame::runGame()
{
	m_Board.loadBoard(m_Window);

	while (m_Window.isOpen())
	{
		readInput();
		update();
		draw();
	}
}

ChessGame& ChessGame::getInstance()
{
	static ChessGame chessGame;
	return chessGame;
}

ChessGame::~ChessGame()
{
}
