#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ChessGame.h"

int main()
{
	ChessGame::getInstance(sf::VideoMode(700, 700), "Chess", sf::Style::Default).runGame();
	return 0;
}