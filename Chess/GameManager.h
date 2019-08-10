#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GameObject.h"
#include "Collection.h"

class Player;
	
class GameManager
{
private:
	sf::RenderWindow m_Window;
	sf::Event m_Event;
	std::vector<GameObject*> m_GameObjects;
	std::vector<Collection*> m_GameObjectContainers;
	Board m_Board;
	Player m_WhitePlayer;
	Player m_BlackPlayer;

	GameManager();
public:
	static GameManager& getInstance();
	void runGame();
	void addGameObject(GameObject* gameObject);
	void removeGameObject(GameObject* gameObject);
	void readInput();
	void update();
	void draw();
	~GameManager();
};

