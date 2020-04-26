 #include "pch.h"
#include "King.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"
#include <iostream>


King::King(const sf::Vector2f& position, const sf::Color& color) : King(position, -1, color)
{
}

King::King(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
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
	//Must set the origin and position only after setting texture to apply the origin correctly
	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setPosition(position);
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

void King::move(Square& square, bool isMockingMove)
{
	if (!isMockingMove && square == m_CastleSquareId)
		m_MoveValidator->castle();
	Piece::move(square, isMockingMove);
}

bool King::controlsSquare(const Square& square, const Board& board) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference + yDifference == 1) || (xDifference == yDifference) && (xDifference == 1);
}

bool King::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	if (isCastling(square, board))
	{
		bool castleIsLegal = m_MoveValidator->castleIsLegal(square, *this);
		if (castleIsLegal)
			m_CastleSquareId = square.getId();
		return castleIsLegal;
	}

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}

King::~King()
{
}
