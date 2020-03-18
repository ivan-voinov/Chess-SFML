#include "pch.h"
#include <iostream>
#include "Bishop.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Player.h"


Bishop::Bishop(const sf::Vector2f& position, const sf::Color& color) :
	Piece(position, color)
{
	try
	{
		std::string bishopPath;

		if (color == sf::Color::Black)
			bishopPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_BISHOP);
		else
			bishopPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_BISHOP);

		if (!m_PieceTexture.loadFromFile(bishopPath))
			throw FileException("Error loading the texture from file: " + bishopPath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
	m_PieceSprite.setTexture(m_PieceTexture);
}

bool Bishop::controlsSquare(const Square& square, const Player& player, const Player& opponent) const
{
	return Piece::controlsDiagonal(player, opponent, getSquare()->getCoordinates(), square.getCoordinates());
}

bool Bishop::isLegalMove(const Square& square, const Player& player, const Player& opponent)
{
	if (!Piece::isLegalMove(square, player, opponent) || player.isChecked(opponent))
		return false;
	
	return controlsSquare(square, player, opponent);
}

Bishop::~Bishop()
{
}
