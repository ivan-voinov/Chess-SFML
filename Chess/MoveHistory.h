#pragma once
#include <SFML/Graphics.hpp>
#include "Move.h"


class MoveHistory
{
private:
	std::vector<Move> m_Moves;

public:
	void rewindLastMove();
	void addMove(Move& move);
	Move& getLastMove();
};

