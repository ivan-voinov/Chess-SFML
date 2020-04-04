#include "pch.h"
#include <iostream>
#include "Queen.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Bishop.h"
#include "Board.h"

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

	return controlsSquare(square, board);
}


Queen::~Queen()
{
}
