#include "pch.h"
#include "Queen.h"
#include "FilePaths.h"
#include "FileException.h"
#include <iostream>


Queen::Queen(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color) :
	Piece(position, coordinates, color)
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

bool Queen::isLegalMove(const Square& square)
{
	return false;
}


Queen::~Queen()
{
}
