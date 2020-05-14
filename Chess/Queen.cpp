#include "pch.h"
#include "Queen.h"
#include "Square.h"
#include "IMoveValidator.h"
#include "Colors.h"
#include "GameManager.h"
#include "ILineValidator.h"

Queen::Queen(const sf::Vector2f& position, const sf::Color& color) : Queen(position, -1, color)
{
}

Queen::Queen(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture* queenPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteQueen") :
		textureManager.getResource("blackQueen");

	if (queenPath)
		setSpriteTexture(*queenPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Queen::onSuccessfulMove()
{
}

bool Queen::controlsSquare(const Square& square) const
{
	const Square& currentSquare = *getSquare();
	return m_LineValidator->LineIsFree(currentSquare, square) || m_LineValidator->diagonalIsFree(currentSquare, square);
}

bool Queen::isLegalMove(Square& square)
{
	if (!Piece::isLegalMove(square))
		return false;

	return controlsSquare(square) && m_MoveValidator->isLegalMove(square, *this);
}

Queen::~Queen()
{
}
