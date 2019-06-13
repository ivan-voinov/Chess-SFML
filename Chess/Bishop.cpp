#include "pch.h"
#include "Bishop.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include <iostream>


Bishop::Bishop(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color) :
	Piece(position, coordinates, color)
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

void Bishop::move(const sf::Vector2f& position)
{
	this->m_PieceSprite.setPosition(position);
}

bool Bishop::isLegalMove(const Square& square)
{
	sf::Vector2i coordinates = square.getCoordinates();

	if (coordinates.x - m_Coordinates.x == coordinates.y - m_Coordinates.y)
		return true;
	return false;
}



Bishop::~Bishop()
{
}
