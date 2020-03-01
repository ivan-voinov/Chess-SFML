#pragma once
#define NDEBUG
#include <SFML/Graphics.hpp>
#include <cassert>
#include <unordered_map>
#include "Board.h"
#include "GameObject.h"
#include "ChessLogic.h"

class Player;
	
class GameManager
{
private:
	sf::RenderWindow m_Window;
	sf::Event m_Event;
	std::vector<std::unique_ptr<GameObject>> m_GameObjects;
	Board m_Board;
	Player m_WhitePlayer;
	Player m_BlackPlayer;
	ChessLogic m_ChessLogic;

	GameManager();
public:
	static GameManager& getInstance();
	void runGame();
	void addGameObject(std::unique_ptr<GameObject> gameObject);
	void removeGameObject(int id);
	void readInput();
	void update();
	void draw();

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

