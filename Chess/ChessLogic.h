#pragma once
#include "Player.h"
#include "Board.h"
#include <SFML/Graphics.hpp>

class ChessLogic
{
private:
	Board* m_Board;
	Player* m_WhitePlayer;
	Player* m_BlackPlayer;

public:
	ChessLogic(Board* board, Player* whitePlayer, Player* blackPlayer);
	void onClick(sf::RenderWindow& window);
	~ChessLogic();
};

