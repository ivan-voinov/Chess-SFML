#include "pch.h"
#include "Move.h"
#include "Piece.h"


Move::Move(int startSquareId, int destSquareId, int activePiece) :
	m_StartSquareId(startSquareId),
	m_DestSquareId(destSquareId),
	m_ActivePiece(activePiece)
{
}

Move::Move(int startSquareId, int destSquareId, int activePiece, std::unique_ptr<Piece> capturedPiece) :
	Move(startSquareId, destSquareId, activePiece)
{
	m_CapturedPiece = std::move(capturedPiece);
}
