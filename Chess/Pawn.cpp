#include "pch.h"
#include "Pawn.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include <iostream>


Pawn::Pawn(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color) :
	Piece(position, coordinates, color)
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
	int changeInX = abs(m_Coordinates.x - square.getCoordinates().x);
	int changeInY = abs(m_Coordinates.y - square.getCoordinates().y);

	//TO DO: force the pawn to move only forward
	if (changeInX > 0 && changeInY == 0)
		return true;

	return false;
}

Pawn::~Pawn()
{
}
