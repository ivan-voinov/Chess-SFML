#include "pch.h"
#include "Rook.h"
#include "FilePaths.h"
#include "FileException.h"
#include <iostream>


Rook::Rook(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color) :
	Piece(position, coordinates, color)
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

bool Rook::isLegalMove(const Square& square)
{
	return false;
}


Rook::~Rook()
{
}
