#include "pch.h"
#include "King.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"
#include <iostream>


King::King(const sf::Vector2f& position, const sf::Color& color) :
	Piece(position, color)
{
	try
	{
		std::string kingPath;

		if (color == sf::Color::Black)
			kingPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_KING);
		else
			kingPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_KING);

		if (!m_PieceTexture.loadFromFile(kingPath))
			throw FileException("Error loading the texture from file: " + kingPath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
	m_PieceSprite.setTexture(m_PieceTexture);
}

void King::onSuccessfulMove()
{
	m_HasCastle = false;
}

bool King::isCastling(const Square& square, const Board& board) const
{
	sf::Vector2i squareCoords = square.getCoordinates();
	if (Colors::isWhite(m_Color))
	{
		return 
			m_HasCastle &&
			squareCoords.x == 7 && 
			(squareCoords.y == 2 || squareCoords.y == 6) &&
			board.LineIsFree(*getSquare(), square);
	}
	else
	{
		return 
			m_HasCastle && 
			squareCoords.x == 0 && 
			(squareCoords.y == 2 || squareCoords.y == 6) && 
			board.LineIsFree(*getSquare(), square);
	}
}

bool King::controlsSquare(const Square& square, const Board& board) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference + yDifference == 1) || (xDifference == yDifference) && (xDifference == 1);
}

bool King::isLegalMove(Square & square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	if (isCastling(square, board))
	{
		//Let player know that a special rule for castling needs to be applied
		notifyObserver("CASTLE", square, board);

		//Need to return false to avoid making another move to the same square
		return false;
	}

	return controlsSquare(square, board);
}

King::~King()
{
}
