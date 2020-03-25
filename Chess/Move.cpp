#include "pch.h"
#include "Move.h"
#include "Piece.h"

Move::Move(int startSquareId, int destSquareId)
{
	m_StartSquareId = startSquareId;
	m_DestSquareId = destSquareId;
}
