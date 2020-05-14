#include "pch.h"
#include "GameManager.h"
#include "GameObject.h"

#define MAX_FPS 60

GameManager::GameManager() : m_WindowDimensions(700, 700)
{
	m_Window.create(sf::VideoMode(m_WindowDimensions.x, m_WindowDimensions.y), "Chess", sf::Style::Default);
	m_Window.setFramerateLimit(MAX_FPS);
}

const sf::Vector2u GameManager::getWindowDimensions() const
{
	return m_WindowDimensions;
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
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_Window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_MouseButtonIsDown = true;
					notify(event, sf::Mouse::getPosition(m_Window));
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (m_MouseButtonIsDown && m_Dragging && event.mouseButton.button == sf::Mouse::Left)
				{
					notify(event, sf::Mouse::getPosition(m_Window));
				}
				m_MouseButtonIsDown = false;
				m_Dragging = false;
				break;

			case sf::Event::MouseMoved:
				if (m_MouseButtonIsDown)
				{
					m_Dragging = true;
					notify(event, sf::Mouse::getPosition(m_Window));
				}
				break;

			case sf::Event::Resized:
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				m_Window.setView(sf::View(visibleArea));
				break;
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

ResourceManager<sf::Texture>& GameManager::getTextureManager()
{
	return m_TextureManager;
}

ResourceManager<sf::SoundBuffer>& GameManager::getAudioManager()
{
	return m_AudioManager;
}

ResourceManager<sf::Font>& GameManager::getFontManager()
{
	return m_FontManager;
}

void GameManager::runGame()
{
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
