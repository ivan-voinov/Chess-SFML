#include "pch.h"
#include "GameManager.h"
#include "Player.h"
#include "GameObject.h"

GameManager::GameManager()
{
	m_Window.create(sf::VideoMode(700, 700), "Chess", sf::Style::Default);
	m_Window.setFramerateLimit(60);
}

void GameManager::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	m_GameObjects.push_back(std::move(gameObject));
}

void GameManager::removeGameObject(int id)
{
	m_GameObjects.erase(std::remove_if(
		m_GameObjects.begin(), 
		m_GameObjects.end(), 
		[id](std::unique_ptr<GameObject>& gmObj) {return *gmObj.get() == id;}));
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
	for (const auto& gameObject : m_GameObjects)
		m_Window.draw(*gameObject.get());
	m_Window.display();
}

void GameManager::runGame()
{
	m_ChessLogic.initializeGame(m_Window);
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
