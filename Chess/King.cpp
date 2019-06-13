#include "pch.h"
#include "King.h"
#include "FilePaths.h"
#include "FileException.h"
#include <iostream>


King::King(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color) :
	Piece(position, coordinates, color)
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
	return false;
}

King::~King()
{
}
