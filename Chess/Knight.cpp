#include "pch.h"
#include <iostream>
#include "Knight.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"


Knight::Knight(const sf::Vector2f& position, const sf::Color& color) : Knight(position, -1, color)
{
}

Knight::Knight(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	std::string knightPath;
	if (color == sf::Color::Black)
		knightPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_KNIGHT);
	else
		knightPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_KNIGHT);

	loadTexture(color, knightPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Knight::onSuccessfulMove()
{
}

bool Knight::controlsSquare(const Square& square, const Board& board) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference == 2 && yDifference == 1) || (xDifference == 1 && yDifference == 2);
}

bool Knight::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}

Knight::~Knight()
{
}
