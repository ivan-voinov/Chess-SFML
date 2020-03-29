#include "pch.h"
#include <iostream>
#include "Rook.h"
#include "FilePaths.h"
#include "FileException.h"
#include "Square.h"
#include "Board.h"


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

void Rook::onSuccessfulMove()
{
	m_HasCastled = false;
}

bool Rook::controlsSquare(const Square& square, const Board& board) const
{
	return board.LineIsFree(*getSquare(), square);
}

bool Rook::isLegalMove(const Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	return controlsSquare(square, board);
}


Rook::~Rook()
{
}
