#include "pch.h"
#include "MoveHistory.h"


void MoveHistory::rewindLastMove()
{
	m_Moves.pop_back();
}

void MoveHistory::addMove(const Move& move)
{
	m_Moves.push_back(move);
}

Move& MoveHistory::getLastMove()
{
	return m_Moves.back();
}
