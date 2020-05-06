#include "pch.h"
#include "Knight.h"
#include "Square.h"
#include "MoveValidator.h"
#include "Colors.h"
#include "GameManager.h"


Knight::Knight(const sf::Vector2f& position, const sf::Color& color) : Knight(position, -1, color)
{
}

Knight::Knight(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	const ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture& knightPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteKnight") :
		textureManager.getResource("blackKnight");

	setSpriteTexture(knightPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Knight::onSuccessfulMove()
{
}

bool Knight::controlsSquare(const Square& square, const Board& board) const
{
	sf::Vector2i squareCoordinates = square.getCoordinates();
	sf::Vector2i thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference == 2 && yDifference == 1) || (xDifference == 1 && yDifference == 2);
}

bool Knight::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}

Knight::~Knight()
{
}
