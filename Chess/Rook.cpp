#include "pch.h"
#include "Rook.h"
#include "Square.h"
#include "MoveValidator.h"
#include "Colors.h"
#include "GameManager.h"
#include "ILineValidator.h"

Rook::Rook(const sf::Vector2f& position, const sf::Color& color) : Rook(position, -1, color)
{
}

Rook::Rook(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	const ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture& rookPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteRook") :
		textureManager.getResource("blackRook");

	setSpriteTexture(rookPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

bool Rook::hasCastle() const
{
	return m_HasCastle;
}

void Rook::onSuccessfulMove()
{
	m_HasCastle = false;
}

bool Rook::controlsSquare(const Square& square) const
{
	return m_LineValidator->LineIsFree(*getSquare(), square);
}

bool Rook::isLegalMove(Square& square)
{
	if (!Piece::isLegalMove(square))
		return false;

	return controlsSquare(square) && m_MoveValidator->isLegalMove(square, *this);
}


Rook::~Rook()
{
}
