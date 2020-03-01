#pragma once
#include "Player.h"
#include "Board.h"
#include <SFML/Graphics.hpp>

class ChessLogic
{
public:
	enum class SquareState
	{
		IS_FREE,
		HAS_ENEMY_PIECE,
		HAS_FRIENDLY_PIECE,
		IS_BLOCKED
	};

private:
	Board* m_Board;
	Player* m_WhitePlayer;
	Player* m_BlackPlayer;
public:
	ChessLogic(Board* board, Player* whitePlayer, Player* blackPlayer);
	void onClick(sf::RenderWindow& window);
	SquareState getSquareState(const Player& activePlayer, const Player& inactivePlayer, const Square& square);
	~ChessLogic();
};

