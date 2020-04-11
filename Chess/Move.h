#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Piece.h"

class Move
{
private:
	int m_StartSquareId;
	int m_DestSquareId;
	int m_ActivePieceId;
	std::unique_ptr<Piece> m_CapturedPiece = nullptr;
	std::function<void()> m_SpecialMoveBehavior;

public:
	Move(int startSquareId, int destSquareId, int activePiece);
	Move(int startSquareId, int destSquareId, int activePiece, std::unique_ptr<Piece> capturedPiece);
	Move(int startSquareId, int destSquareId, int activePiece, std::unique_ptr<Piece> capturedPiece, std::function<void()>* specialMove);

};

