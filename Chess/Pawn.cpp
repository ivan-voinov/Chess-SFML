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

bool Pawn::isMovingForward(const Square& startSquare, const Square& targetSquare) const
{
	if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
	{
		return startSquare.getCoordinates().x - targetSquare.getCoordinates().x < 0;
	}
	else if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
	{
		return startSquare.getCoordinates().x - targetSquare.getCoordinates().x > 0;
	}
}

bool Pawn::hasDoubleMove() const
{
	return m_HasDoubleMove;
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
	Square* startingSquare = getSquare();
	int xDifference = abs(startingSquare->getCoordinates().x - square.getCoordinates().x);
	int yDifference = abs(startingSquare->getCoordinates().y - square.getCoordinates().y);

	if (!Piece::isLegalMove(square, player, opponent) || player.isChecked(opponent))
		return false;

	if (isMovingForward(*startingSquare, square))
	{
		if (hasDoubleMove())
		{
 			if ((xDifference == 1 || xDifference == 2) && yDifference == 0)
			{
				m_HasDoubleMove = false;
				return true;
			}
		}
		else
		{
			if (xDifference == 1 && yDifference == 0)
				return true;
		}
	}
	return false;
}

bool Pawn::reachedEighthRank() const
{
	Square* startingSquare = getSquare();
	return (startingSquare->getCoordinates().x == 0 || startingSquare->getCoordinates().x == 7);
}

Pawn::~Pawn()
{
}
