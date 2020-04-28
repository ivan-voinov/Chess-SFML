#include "pch.h"
#include "Bishop.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"
#include "MoveValidator.h"
#include "Colors.h"


Bishop::Bishop(const sf::Vector2f& position, const sf::Color& color) :
	Bishop (position, -1, color)
{
}

Bishop::Bishop(const sf::Vector2f& position, int squareId, const sf::Color& color) :
	Piece(position, squareId, color)
{
	std::string bishopPath;
	if (color == sf::Color::Black)
		bishopPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_BISHOP);
	else
		bishopPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_BISHOP);

	loadTexture(bishopPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Bishop::onSuccessfulMove()
{
}

bool Bishop::controlsSquare(const Square& square, const Board& board) const
{
	return board.diagonalIsFree(*getSquare(), square);
}

bool Bishop::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;
	
	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}

Bishop::~Bishop()
{
}
