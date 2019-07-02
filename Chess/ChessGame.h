#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GameObject.h"
	
class ChessGame
{
private:
	sf::RenderWindow m_Window;
	sf::Event m_Event;
	Board m_Board;
	std::vector<GameObject*> m_GameObjects;
	std::vector<sf::Drawable*> m_DrawableObjects;

	ChessGame();
public:
	static ChessGame& getInstance();
	void runGame();
	void addGameObject(GameObject* gameObject);
	void addDrawableObject(sf::Drawable* drawableObject);
	void removeGameObject(GameObject* gameObject);
	void removeDrawableObject(sf::Drawable* drawableObject);
	void readInput();
	void update();
	void draw();
	~ChessGame();
};

