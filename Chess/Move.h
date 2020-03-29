#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

class Move
{
private:
	int m_StartSquareId;
	int m_DestSquareId;
	int m_ActivePiece;
	std::unique_ptr<Piece> m_CapturedPiece = nullptr;

public:
	Move(int startSquareId, int destSquareId, int activePiece);
	Move(int startSquareId, int destSquareId, int activePiece, std::unique_ptr<Piece> capturedPiece);
};

