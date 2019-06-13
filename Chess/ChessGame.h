#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "ObjectDrawer.h"
	
class ChessGame
{
private:
	sf::RenderWindow m_Window;
	sf::Event m_Event;
	Board m_Board;
	ObjectDrawer m_ObjectDrawer;

	ChessGame(sf::VideoMode mode, const std::string &title, sf::Uint32 style);
	void readInput();
	void update();
	void draw();

public:
	static ChessGame& getInstance(sf::VideoMode mode, const std::string &title, sf::Uint32 style);
	void runGame();
	~ChessGame();
};

