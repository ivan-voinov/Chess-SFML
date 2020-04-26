#include "pch.h"
#include <iostream>
#include "Rook.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"


Rook::Rook(const sf::Vector2f& position, const sf::Color& color) : Rook(position, -1, color)
{
}

Rook::Rook(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	std::string rookPath;
	if (color == sf::Color::Black)
		rookPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_ROOK);
	else
		rookPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_ROOK);

	loadTexture(color, rookPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

bool Rook::hasCastle() const
{
	return m_HasCastle;
}

void Rook::onSuccessfulMove()
{
	m_HasCastle = false;
}

bool Rook::controlsSquare(const Square& square, const Board& board) const
{
	return board.LineIsFree(*getSquare(), square);
}

bool Rook::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}


Rook::~Rook()
{
}
