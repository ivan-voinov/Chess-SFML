#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

class Move
{
private:
	int m_StartSquareId;
	int m_DestSquareId;

public:
	Move(int startSquareId, int destSquareId);
};

