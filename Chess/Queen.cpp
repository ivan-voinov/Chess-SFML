#include "pch.h"
#include "Queen.h"
#include "Square.h"
#include "Board.h"
#include "MoveValidator.h"
#include "Colors.h"
#include "GameManager.h"

Queen::Queen(const sf::Vector2f& position, const sf::Color& color) : Queen(position, -1, color)
{
}

Queen::Queen(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	const ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture& queenPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteQueen") :
		textureManager.getResource("blackQueen");

	setSpriteTexture(queenPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Queen::onSuccessfulMove()
{
}

bool Queen::controlsSquare(const Square& square, const Board& board) const
{
	const Square& currentSquare = *getSquare();
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
