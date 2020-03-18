#include "pch.h"
#include "King.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Player.h"
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

bool King::controlsSquare(const Square& square, const Player& player, const Player& opponent) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference + yDifference == 1) || (xDifference == yDifference) && (xDifference == 1);
}

bool King::isLegalMove(const Square& square, const Player& player, const Player& opponent)
{
	if (!Piece::isLegalMove(square, player, opponent))
		return false;

	if (controlsSquare(square, player, opponent))
	{
		return !opponent.controlsSquare(square, player);
	}
}

King::~King()
{
}
