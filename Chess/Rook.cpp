#include "pch.h"
#include <iostream>
#include "Rook.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Player.h"


Rook::Rook(const sf::Vector2f& position, const sf::Color& color) :
	Piece(position, color)
{
	try
	{
		std::string rookPath;

		if (color == sf::Color::Black)
			rookPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_ROOK);
		else
			rookPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_ROOK);

		if (!m_PieceTexture.loadFromFile(rookPath))
			throw FileException("Error loading the texture from file: " + rookPath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
	m_PieceSprite.setTexture(m_PieceTexture);
}


bool Rook::controlsSquare(const Square& square, const Player& player, const Player& opponent) const
{
	return Piece::controlsLine(player, opponent, getSquare()->getCoordinates(), square.getCoordinates());
}

bool Rook::isLegalMove(const Square& square, const Player& player, const Player& opponent)
{
	if (!Piece::isLegalMove(square, player, opponent) || player.isChecked(opponent))
		return false;

	return controlsSquare(square, player, opponent);
}


Rook::~Rook()
{
}
