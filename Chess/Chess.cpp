#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ChessGame.h"

int main()
{
	ChessGame::getInstance().runGame();
	return 0;
}