#include "pch.h"
#include "Bishop.h"
#include "Square.h"
#include "Board.h"
#include "MoveValidator.h"
#include "Colors.h"
#include "GameManager.h"


Bishop::Bishop(const sf::Vector2f& position, const sf::Color& color) :
	Bishop (position, -1, color)
{
}

Bishop::Bishop(const sf::Vector2f& position, int squareId, const sf::Color& color) :
	Piece(position, squareId, color)
{
	const ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture& bishopPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteBishop") :
		textureManager.getResource("blackBishop");

	setSpriteTexture(bishopPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
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
