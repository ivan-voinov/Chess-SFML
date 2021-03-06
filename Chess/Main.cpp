#include "pch.h"
#include "GameManager.h"
#include "ChessLogic.h"

int main()
{
	GameManager::getInstance();
	ChessLogic chess(GameManager::getInstance().getWindowDimensions());
	chess.initializeGame();
	GameManager::getInstance().attach(chess);
	GameManager::getInstance().runGame();
	return 0;
}