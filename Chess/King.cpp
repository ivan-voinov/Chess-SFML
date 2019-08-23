#include "pch.h"
#include "King.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
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

bool King::isLegalMove(const Square& square)
{
	int changeInX = abs(m_Square->getCoordinates().x - square.getCoordinates().x);
	int changeInY = abs(m_Square->getCoordinates().y - square.getCoordinates().y);

	if ((changeInX + changeInY == 1) || (changeInX == changeInY && changeInX == 1))
		return true;

	return false;
}

King::~King()
{
}
