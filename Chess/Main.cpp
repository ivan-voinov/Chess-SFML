#include "pch.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{
	GameManager::getInstance().runGame();
	return 0;
}