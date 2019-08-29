#include "pch.h"
#include "Pawn.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include <iostream>


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

bool Pawn::isStartingSquare(const sf::Vector2i& coordinates) const
{
	if (coordinates.x == 1 || coordinates.x == 6)
		return true;
	return false;
}

bool Pawn::isLegalMove(const Square& square)
{
	int changeInX = abs(m_Square->getCoordinates().x - square.getCoordinates().x);
	int changeInY = abs(m_Square->getCoordinates().y - square.getCoordinates().y);

	if (m_Color == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
	{
		//Check to force the pawn to move only forward
		if (m_Square->getCoordinates().x - square.getCoordinates().x > 0)
		{
			//Check if the pawn can move two spaces or not
			if (isStartingSquare(m_Square->getCoordinates()))
			{
				if ((changeInX == 1 || changeInX == 2) && changeInY == 0)
					return true;
			}
			else
			{
				if (changeInX == 1 && changeInY == 0)
					return true;
			}
		}
	}
	else
	{
		//Check to force the pawn to move only forward
		if (m_Square->getCoordinates().x - square.getCoordinates().y < 0)
		{
			if (isStartingSquare(m_Square->getCoordinates()))
			{
				if ((changeInX == 1 || changeInX == 2) && changeInY == 0)
					return true;
			}
			else
			{
				if (changeInX == 1 && changeInY == 0)
					return true;
			}
		}
	}

	return false;
}

bool Pawn::reachedEighthRank() const
{
	if (m_Square->getCoordinates().x == 0 || m_Square->getCoordinates().x == 7)
		return true;

	return false;
}

Pawn::~Pawn()
{
}
