#include "pch.h"
#include <iostream>
#include "Pawn.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Player.h"


Pawn::Pawn(const sf::Vector2f& position, const sf::Color& color) :
	Piece(position,	 color)
{
	try
	{
		std::string pawnPath;

		if (color == sf::Color::Black)
			pawnPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_PAWN);
		else
			pawnPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_PAWN);

		if (!m_PieceTexture.loadFromFile(pawnPath))
			throw FileException("Error loading the texture from file: " + pawnPath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
	m_PieceSprite.setTexture(m_PieceTexture);
}

bool Pawn::movesForward(const Square& square, const Player& player, const Player& opponent) const
{
	const Square& currentSuare = *getSquare();
	int xDifference = abs(currentSuare.getCoordinates().x - square.getCoordinates().x);
	int yDifference = abs(currentSuare.getCoordinates().y - square.getCoordinates().y);

	if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::BLACK) &&
		currentSuare.getCoordinates().x - square.getCoordinates().x > 0)
	{
		return false;
	}
	else if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::WHITE) &&
		currentSuare.getCoordinates().x - square.getCoordinates().x < 0)
	{
		return false;
	}

	if (xDifference == 2 && yDifference == 0)
		return m_HasDoubleMove && !doubleMoveIsBlocked(square, player, opponent);
	else 
		return xDifference == 1 && yDifference == 0 && !opponent.hasPieceOnSquare(square.getCoordinates());
}

bool Pawn::capturesPiece(const Square& square, const Player& player, const Player& opponent) const
{
	sf::Vector2i currentCoords = getSquare()->getCoordinates();
	sf::Vector2i targetCoords = square.getCoordinates();

	if ((targetCoords.y == currentCoords.y + 1 || targetCoords.y == currentCoords.y - 1))
	{
		if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
		{
			return (targetCoords.x == currentCoords.x + 1) ? opponent.hasPieceOnSquare(square.getCoordinates()) : false;
		}
		else if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
		{
			return (targetCoords.x == currentCoords.x - 1) ? opponent.hasPieceOnSquare(square.getCoordinates()) : false;
		}
	}
	return false;
}

bool Pawn::doubleMoveIsBlocked(const Square& targetSquare, const Player& player, const Player& opponent) const
{
	sf::Vector2i blockingSquareCoords;
	if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
	{
		blockingSquareCoords = std::move(sf::Vector2i(targetSquare.getCoordinates().x - 1, targetSquare.getCoordinates().y));
	}
	else if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
	{
		blockingSquareCoords = sf::Vector2i(targetSquare.getCoordinates().x + 1, targetSquare.getCoordinates().y);
	}
	return player.hasPieceOnSquare(blockingSquareCoords) || opponent.hasPieceOnSquare(blockingSquareCoords);
}

bool Pawn::freeToMove(const Square& targetSquare, const Player& player, const Player& opponent) const
{
	if (m_HasDoubleMove)
	{
		if (doubleMoveIsBlocked(targetSquare, player, opponent))
			return false;
	}
	return opponent.hasPieceOnSquare(targetSquare.getCoordinates());
}

bool Pawn::controlsSquare(const Square& square, const Player& player, const Player& opponent) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference + yDifference == 2) && (xDifference == yDifference);
}

bool Pawn::isLegalMove(const Square& square, const Player& player, const Player& opponent)
{
	if (!Piece::isLegalMove(square, player, opponent) || player.isChecked(opponent))
		return false;

	if (movesForward(square, player, opponent))
	{
		m_HasDoubleMove = false;
		return true;
	}
	else
	{
		if (capturesPiece(square, player, opponent))
		{
			m_HasDoubleMove = false;
			return true;
		}
	}
	return false;
}

bool Pawn::reachedEighthRank() const
{
	Square* currentSquare = getSquare();
	if (getColor() == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
		return currentSquare->getCoordinates().x == 7;
	else if (getColor() == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
		return currentSquare->getCoordinates().x == 1;
}

Pawn::~Pawn()
{
}
