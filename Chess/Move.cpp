#include "pch.h"
#include "Move.h"
#include "Piece.h"


Move::Move(int startSquareId,
	int destSquareId,
	int activePieceId) : Move(startSquareId, destSquareId, activePieceId, nullptr, nullptr)
{
}

Move::Move(int startSquareId,
	int destSquareId,
	int activePieceId,
	std::unique_ptr<Piece> capturedPiece) :	Move(startSquareId, destSquareId, activePieceId, std::move(capturedPiece), nullptr)
{
}

Move::Move(int startSquareId,
	int destSquareId,
	int activePieceId,
	std::unique_ptr<Piece> capturedPiece,
	std::function<void()>* specialMove)
{
	m_StartSquareId = startSquareId;
	m_DestSquareId = destSquareId;
	m_ActivePieceId = activePieceId;
	m_CapturedPiece = std::move(capturedPiece);
	m_SpecialMoveBehavior = *specialMove;
}
