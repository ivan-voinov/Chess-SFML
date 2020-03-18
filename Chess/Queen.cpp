#include "pch.h"
#include <iostream>
#include "Queen.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Player.h"
#include "Bishop.h"


Queen::Queen(const sf::Vector2f& position, const sf::Color& color) :
	Piece(position, color)
{
	try
	{
		std::string queenPath;

		if (color == sf::Color::Black)
			queenPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_QUEEN);
		else
			queenPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_QUEEN);

		if (!m_PieceTexture.loadFromFile(queenPath))
			throw FileException("Error loading the texture from file: " + queenPath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
	m_PieceSprite.setTexture(m_PieceTexture);
}

bool Queen::controlsSquare(const Square& square, const Player& player, const Player& opponent) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();

	return Piece::controlsLine(player, opponent, squareCoordinates, thisCoordinates) ||
		Piece::controlsDiagonal(player, opponent, squareCoordinates, thisCoordinates);
}

bool Queen::isLegalMove(const Square& square, const Player& player, const Player& opponent)
{
	if (!Piece::isLegalMove(square, player, opponent) || player.isChecked(opponent))
		return false;

	return controlsSquare(square, player, opponent);
}


Queen::~Queen()
{
}
