#include "pch.h"
#include "Knight.h"
#include "FilePaths.h"
#include "FileException.h"
#include <iostream>


Knight::Knight(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color) :
	Piece(position, coordinates, color)
{
	try
	{
		std::string knightPath;

		if (color == sf::Color::Black)
			knightPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::BLACK_KNIGHT);
		else
			knightPath = FilePaths::getInstance().getFilePath(FilePaths::FileNames::WHITE_KNIGHT);

		if (!m_PieceTexture.loadFromFile(knightPath))
			throw FileException("Error loading the texture from file: " + knightPath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
	m_PieceSprite.setTexture(m_PieceTexture);
}

bool Knight::isLegalMove(const Square& square)
{
	return false;
}

Knight::~Knight()
{
}
