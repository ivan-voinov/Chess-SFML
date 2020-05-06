 #include "pch.h"
#include "King.h"
#include "Square.h"
#include "Board.h"
#include "MoveValidator.h"
#include "Colors.h"
#include "GameManager.h"

King::King(const sf::Vector2f& position, const sf::Color& color) : King(position, -1, color)
{
}

King::King(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	const ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture& kingPath = Colors::isWhite(m_Color) ? textureManager.getResource("whiteKing") :
		textureManager.getResource("blackKing");

	setSpriteTexture(kingPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void King::onSuccessfulMove()
{
	m_HasCastle = false;
}

bool King::isCastling(const Square& square, const Board& board) const
{
	const sf::Vector2i& squareCoords = square.getCoordinates();
	if (Colors::isWhite(m_Color))
	{
		return 
			m_HasCastle &&
			squareCoords.x == 7 && 
			(squareCoords.y == 2 || squareCoords.y == 6) &&
			board.LineIsFree(*getSquare(), square);
	}
	else
	{
		return 
			m_HasCastle && 
			squareCoords.x == 0 && 
			(squareCoords.y == 2 || squareCoords.y == 6) && 
			board.LineIsFree(*getSquare(), square);
	}
}

void King::move(Square& square, bool isMockingMove)
{
	const Square& currentSquare = *getSquare();
	//Detect castle: If the target square is 2 squares away from the king, that means castling rules should be applied
	if (!isMockingMove && abs(square.getCoordinates().y - currentSquare.getCoordinates().y) == 2)
		m_MoveValidator->castle(square, *this);
	Piece::move(square, isMockingMove);
}

bool King::controlsSquare(const Square& square, const Board& board) const
{
	const sf::Vector2i& squareCoordinates = square.getCoordinates();
	const sf::Vector2i& thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference == yDifference) && (xDifference == 1) || (xDifference + yDifference == 1);
}

bool King::isLegalMove(Square& square, const Board& board)
{
	if (!Piece::isLegalMove(square, board))
		return false;

	if (isCastling(square, board))
		return m_MoveValidator->castleIsLegal(square, *this);

	return controlsSquare(square, board) && m_MoveValidator->isLegalMove(square, *this);
}

King::~King()
{
}
