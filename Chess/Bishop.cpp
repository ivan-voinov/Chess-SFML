#include "pch.h"
#include <iostream>
#include "Bishop.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"


Bishop::Bishop(const sf::Vector2f& position, const sf::Color& color) :
	Bishop (position, -1, color)
{
}

Bishop::Bishop(const sf::Vector2f& position, int squareId, const sf::Color& color) :
	Piece(position, squareId, color)
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
	//Must set the origin and position only after setting texture to apply the origin correctly
	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setPosition(position);
}

void Bishop::onSuccessfulMove()
{
}

bool Bishop::controlsSquare(const Square& square, const Board& board) const
{
	return board.diagonalIsFree(*getSquare(), square);
}

bool Bishop::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;
	
	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}

Bishop::~Bishop()
{
}
