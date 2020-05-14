#include "pch.h"
#include "Bishop.h"
#include "Square.h"
#include "IMoveValidator.h"
#include "Colors.h"
#include "GameManager.h"
#include "ILineValidator.h"


Bishop::Bishop(const sf::Vector2f& position, const sf::Color& color) :
	Bishop (position, -1, color)
{
}

Bishop::Bishop(const sf::Vector2f& position, int squareId, const sf::Color& color) :
	Piece(position, squareId, color)
{
	ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture* bishopPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteBishop") :
		textureManager.getResource("blackBishop");

	if (bishopPath)
		setSpriteTexture(*bishopPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Bishop::onSuccessfulMove()
{
}

bool Bishop::controlsSquare(const Square& square) const
{
	return m_LineValidator->diagonalIsFree(*getSquare(), square);
}

bool Bishop::isLegalMove(Square& square)
{
	if (!Piece::isLegalMove(square))
		return false;
	
	return controlsSquare(square) && m_MoveValidator->isLegalMove(square, *this);
}

Bishop::~Bishop()
{
}
