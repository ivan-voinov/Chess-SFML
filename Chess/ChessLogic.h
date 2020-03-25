#pragma once
#include "Player.h"
#include "Board.h"
#include "MoveHistory.h"
#include <SFML/Graphics.hpp>

class ChessLogic
{
private:
	Board m_Board;
	Player m_WhitePlayer;
	Player m_BlackPlayer;
	MoveHistory m_MoveHistory;

public:
	ChessLogic();
	void initializeGame(const sf::RenderWindow& window);
	void onClick(sf::RenderWindow& window);
	~ChessLogic();
};

