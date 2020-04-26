#include "pch.h"
#include <iostream>
#include "Pawn.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"

Pawn::Pawn(const sf::Vector2f& position, const sf::Color& color) : Pawn(position, -1, color)
{
}

Pawn::Pawn(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	std::string pawnPath;
	if (color == sf::Color::Black)
		pawnPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_PAWN);
	else
		pawnPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_PAWN);

	loadTexture(pawnPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Pawn::move(Square& square, bool isMockingMove)
{
	if (!isMockingMove && square == m_EnPassantSquareId)
	{
		m_MoveValidator->enPassant();
	}
	Piece::move(square, isMockingMove);
}

void Pawn::onSuccessfulMove()
{
	sf::Vector2i currentCoords = getSquare()->getCoordinates();

	if (Colors::isWhite(m_Color))
	{
		if (m_HasDoubleMove && currentCoords.x == 4)
			m_EnPassantIsActive = true;
	}
	else
	{
		if (m_HasDoubleMove && currentCoords.x == 3)
			m_EnPassantIsActive = true;
	}
	m_HasDoubleMove = false;
}

bool Pawn::moveForwardIsLegal(const Square& square, const Board& board) const
{
	const Square& currentSuare = *getSquare();
	int xDifference = abs(currentSuare.getCoordinates().x - square.getCoordinates().x);
	int yDifference = abs(currentSuare.getCoordinates().y - square.getCoordinates().y);

	if (Colors::isBlack(m_Color) &&
		currentSuare.getCoordinates().x - square.getCoordinates().x > 0)
	{
		return false;
	}
	else if (Colors::isWhite(m_Color) &&
		currentSuare.getCoordinates().x - square.getCoordinates().x < 0)
	{
		return false;
	}

	if (xDifference == 2 && yDifference == 0)
		return m_HasDoubleMove && doubleMoveIsLegal(square, board) && !square.hasEnemyPiece(m_Color);
	else 
		return xDifference == 1 && yDifference == 0 && !square.hasEnemyPiece(m_Color);
}

bool Pawn::capturesPiece(const Square& square, const Board& board) const
{
	if (movesDiagonally(square))
		return square.hasEnemyPiece(m_Color);
	return false;
}

bool Pawn::doubleMoveIsLegal(const Square& square, const Board& board) const
{
	sf::Vector2i blockingSquareCoords;
	if (m_Color == Colors::getColor(Colors::Names::BLACK))
	{
		blockingSquareCoords = std::move(sf::Vector2i(square.getCoordinates().x - 1, square.getCoordinates().y));
	}
	else if (m_Color == Colors::getColor(Colors::Names::WHITE))
	{
		blockingSquareCoords = sf::Vector2i(square.getCoordinates().x + 1, square.getCoordinates().y);
	}
	return board.getSquare(blockingSquareCoords)->isFree();
}

bool Pawn::freeToMove(const Square& square, const Board& board) const
{
	if (m_HasDoubleMove && doubleMoveIsLegal(square, board))
		return false;

	return square.hasEnemyPiece(m_Color);
}

bool Pawn::enPassant(const Square& square, const Board& board) const
{
	return square.isFree() && movesDiagonally(square);
}

bool Pawn::movesDiagonally(const Square& square) const
{
	sf::Vector2i currentCoords = getSquare()->getCoordinates();
	sf::Vector2i targetCoords = square.getCoordinates();

	if ((targetCoords.y == currentCoords.y + 1 || targetCoords.y == currentCoords.y - 1))
	{
		if (Colors::isBlack(m_Color))
		{
			return (targetCoords.x == currentCoords.x + 1);
		}
		else if (Colors::isWhite(m_Color))
		{
			return (targetCoords.x == currentCoords.x - 1);
		}
	}
	return false;
}

bool Pawn::controlsSquare(const Square& square, const Board& board) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference + yDifference == 2) && (xDifference == yDifference);
}

bool Pawn::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	if (enPassant(square, board))
	{
		bool enPassantIsLegal = m_MoveValidator->enPassantIsLegal(square, *this);
		if (enPassantIsLegal)
			m_EnPassantSquareId = square.getId();
		return enPassantIsLegal;
	}
	if (moveForwardIsLegal(square, board) || capturesPiece(square, board))
	{
		if (canBePromoted(square) && m_MoveValidator->isLegalMove(square, *this))
		{
			//Promotion code
		}
		return m_MoveValidator->isLegalMove(square, *this);
	}
	return false;
}

bool Pawn::canBePromoted(const Square& square) const
{
	if (getColor() == Colors::getColor(Colors::Names::WHITE))
		return square.getCoordinates().x == 0;
	else 
		return square.getCoordinates().x == 7;
}

bool Pawn::enPassantIsActive() const
{
	return m_EnPassantIsActive;
}

void Pawn::deactivateEnPassant()
{
	m_EnPassantIsActive = false;
}

Pawn::~Pawn()
{
}
