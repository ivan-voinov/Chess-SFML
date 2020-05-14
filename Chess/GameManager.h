#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "ResourceManager.h"
#include "Subject.h"
#include "GameObject.h"


class GameManager : public Subject
{
private:
	sf::RenderWindow m_Window;
	ResourceManager<sf::Texture> m_TextureManager;
	ResourceManager<sf::SoundBuffer> m_AudioManager;
	ResourceManager<sf::Font> m_FontManager;
	sf::Vector2f m_OnClickMousePosition;
	bool m_MouseButtonIsDown = false;
	const sf::Vector2u m_WindowDimensions;

	std::vector<std::unique_ptr<GameObject>> m_GameObjects;
	GameManager();
	bool exceededMinDragDistance(const sf::Vector2i& mousePosition) const;

public:
	static GameManager& getInstance();
	const sf::Vector2u getWindowDimensions() const;
	void runGame();
	void addGameObject(std::unique_ptr<GameObject> gameObject);
	void removeGameObject(int id);
	void readInput();
	void update();
	void draw();
	ResourceManager<sf::Texture>& getTextureManager();
	ResourceManager<sf::SoundBuffer>& getAudioManager();
	ResourceManager<sf::Font>& getFontManager();

	template<typename T>
	T* getGameObject(int id)
	{
		GameObject* requested = nullptr;
		for (const auto& gameObject : m_GameObjects)
		{
			requested = gameObject.get();
			if (*requested == id)
			{
				assert(requested && "Err: Requested object doesn't inherit from GameObject");
				return dynamic_cast<T*>(requested);
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> getGameObjects(const std::vector<int>& ids)
	{
		std::vector<T*> requested;
		T* temp = nullptr;
		for (int i = 0; i < ids.size(); i++)
		{
			temp = getGameObject<T>(ids.at(i));
			if (temp != nullptr)
				requested.push_back(temp);
		}
		return requested;
	}
	~GameManager();
};

