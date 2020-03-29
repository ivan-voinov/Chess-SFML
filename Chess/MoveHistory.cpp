#include "pch.h"
#include "MoveHistory.h"


void MoveHistory::rewindLastMove()
{
	m_Moves.pop_back();
}

void MoveHistory::addMove(Move& move)
{
	m_Moves.push_back(std::move(move));
}

Move& MoveHistory::getLastMove()
{
	return m_Moves.back();
}
