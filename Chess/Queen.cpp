#include "pch.h"
#include <iostream>
#include "Queen.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"

Queen::Queen(const sf::Vector2f& position, const sf::Color& color) : Queen(position, -1, color)
{
}

Queen::Queen(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
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
	//Must set the origin and position only after setting the texture to apply the origin correctly
	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setPosition(position);
}

void Queen::onSuccessfulMove()
{
}

bool Queen::controlsSquare(const Square& square, const Board& board) const
{
	Square& currentSquare = *getSquare();
	return board.LineIsFree(currentSquare, square) || board.diagonalIsFree(currentSquare, square);
}

bool Queen::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}


Queen::~Queen()
{
}
