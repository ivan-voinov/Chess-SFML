#include "pch.h"
#include <iostream>
#include "Queen.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"

Queen::Queen(const sf::Vector2f& position, const sf::Color& color) : Queen(position, -1, color)
{
}

Queen::Queen(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	std::string queenPath;
	if (color == sf::Color::Black)
		queenPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_QUEEN);
	else
		queenPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_QUEEN);

	loadTexture(queenPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Queen::onSuccessfulMove()
{
}

bool Queen::controlsSquare(const Square& square, const Board& board) const
{
	Square& currentSquare = *getSquare();
	return board.LineIsFree(currentSquare, square) || board.diagonalIsFree(currentSquare, square);
}

bool Queen::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}


Queen::~Queen()
{
}
