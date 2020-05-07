#include "pch.h"
#include "Pawn.h"
#include "Square.h"
#include "MoveValidator.h"
#include "Colors.h"
#include "GameManager.h"
#include "ILineValidator.h"

Pawn::Pawn(const sf::Vector2f& position, const sf::Color& color) : Pawn(position, -1, color)
{
}

Pawn::Pawn(const sf::Vector2f& position, int squareId, const sf::Color& color) : Piece(position, squareId, color)
{
	const ResourceManager<sf::Texture>& textureManager = GameManager::getInstance().getTextureManager();
	const sf::Texture& pawnPath = Colors::isWhite(m_Color) ? textureManager.getResource("whitePawn") :
		textureManager.getResource("blackPawn");

	setSpriteTexture(pawnPath);
	//Must set the origin and position only after setting texture to apply the origin correctly
	setOriginAndPosition(position);
}

void Pawn::move(Square& square, bool isMockingMove)
{
	Piece::move(square, isMockingMove);
	if (!isMockingMove)
	{
		if (square == m_EnPassantSquareId)
			m_MoveValidator->enPassant(square, *this);
		if (canBePromoted(square))
			m_MoveValidator->onPawnPromotionTriggered(square, *this);
	}
}

void Pawn::onSuccessfulMove()
{
	const sf::Vector2i& currentCoords = getSquare()->getCoordinates();

	if (Colors::isWhite(m_Color))
	{
		if (m_HasDoubleMove && currentCoords.x == 4)
			m_EnPassantIsActive = true;
	}
	else
	{
		if (m_HasDoubleMove && currentCoords.x == 3)
			m_EnPassantIsActive = true;
	}
	m_HasDoubleMove = false;
}

bool Pawn::moveForwardIsLegal(const Square& square) const
{
	const Square& currentSuare = *getSquare();
	int xDifference = abs(currentSuare.getCoordinates().x - square.getCoordinates().x);
	int yDifference = abs(currentSuare.getCoordinates().y - square.getCoordinates().y);

	if (Colors::isBlack(m_Color) &&
		currentSuare.getCoordinates().x - square.getCoordinates().x > 0)
	{
		return false;
	}
	else if (Colors::isWhite(m_Color) &&
		currentSuare.getCoordinates().x - square.getCoordinates().x < 0)
	{
		return false;
	}

	if (xDifference == 2 && yDifference == 0)
		return m_HasDoubleMove && doubleMoveIsLegal(square) && !square.hasEnemyPiece(m_Color);
	else 
		return xDifference == 1 && yDifference == 0 && !square.hasEnemyPiece(m_Color);
}

bool Pawn::capturesPiece(const Square& square) const
{
	if (movesDiagonally(square))
		return square.hasEnemyPiece(m_Color);
	return false;
}

bool Pawn::doubleMoveIsLegal(const Square& square) const
{
	sf::Vector2i blockingSquareCoords;
	if (m_Color == Colors::getColor(Colors::Names::BLACK))
	{
		blockingSquareCoords = std::move(sf::Vector2i(square.getCoordinates().x - 1, square.getCoordinates().y));
	}
	else if (m_Color == Colors::getColor(Colors::Names::WHITE))
	{
		blockingSquareCoords = sf::Vector2i(square.getCoordinates().x + 1, square.getCoordinates().y);
	}
	return m_LineValidator->LineIsFree(*getSquare(), square);
}

bool Pawn::freeToMove(const Square& square) const
{
	if (m_HasDoubleMove && doubleMoveIsLegal(square))
		return false;

	return square.hasEnemyPiece(m_Color);
}

bool Pawn::enPassant(const Square& square) const
{
	return square.isFree() && movesDiagonally(square);
}

bool Pawn::movesDiagonally(const Square& square) const
{
	const sf::Vector2i& currentCoords = getSquare()->getCoordinates();
	const sf::Vector2i& targetCoords = square.getCoordinates();

	if ((targetCoords.y == currentCoords.y + 1 || targetCoords.y == currentCoords.y - 1))
	{
		if (Colors::isBlack(m_Color))
		{
			return (targetCoords.x == currentCoords.x + 1);
		}
		else if (Colors::isWhite(m_Color))
		{
			return (targetCoords.x == currentCoords.x - 1);
		}
	}
	return false;
}

bool Pawn::controlsSquare(const Square& square) const
{
	const sf::Vector2i& squareCoordinates = square.getCoordinates();
	const sf::Vector2i& thisCoordinates = getSquare()->getCoordinates();
	int xDifference = abs(squareCoordinates.x - thisCoordinates.x);
	int yDifference = abs(squareCoordinates.y - thisCoordinates.y);

	return (xDifference + yDifference == 2) && (xDifference == yDifference);
}

bool Pawn::isLegalMove(Square& square)
{
	if (!Piece::isLegalMove(square))
		return false;

	if (enPassant(square))
	{
		bool enPassantIsLegal = m_MoveValidator->enPassantIsLegal(square, *this);
		if (enPassantIsLegal)
			m_EnPassantSquareId = square.getId();
		return enPassantIsLegal;
	}
	if (moveForwardIsLegal(square) || capturesPiece(square))
	{
		return m_MoveValidator->isLegalMove(square, *this);
	}
	return false;
}

bool Pawn::canBePromoted(const Square& square) const
{
	if (Colors::isWhite(m_Color))
		return square.getCoordinates().x == 0;
	else 
		return square.getCoordinates().x == 7;
}

bool Pawn::enPassantIsActive() const
{
	return m_EnPassantIsActive;
}

void Pawn::deactivateEnPassant()
{
	m_EnPassantIsActive = false;
}

Pawn::~Pawn()
{
}
