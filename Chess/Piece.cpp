#include "pch.h"
#include "Piece.h"
#include "Square.h"
#include "GameManager.h"
#include "Colors.h"


Piece::Piece(const sf::Vector2f& position, const sf::Color& color) : Piece(position, -1, color)
{
}

Piece::Piece(const sf::Vector2f& position, int squareId, const sf::Color& color)
{
	m_Color = color;
	m_SquareId = squareId;
}

void Piece::setSpriteTexture(const sf::Texture& texture)
{
	m_PieceSprite.setTexture(texture);
}

void Piece::setOriginAndPosition(const sf::Vector2f& position)
{
	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setPosition(position);
}

const sf::Color& Piece::getColor() const
{
	return m_Color;
}

Square* Piece::getSquare() const
{
	return GameManager::getInstance().getGameObject<Square>(m_SquareId);
}

void Piece::resize(const double squareSize)
{
	m_PieceSprite.setScale(squareSize / m_PieceSprite.getLocalBounds().width, squareSize / m_PieceSprite.getLocalBounds().height);
}

void Piece::updateSquareState(Square& square, bool isMockingMove)
{
	Square& startSquare = *getSquare();

	startSquare.restoreState();
	if (startSquare.getPreviousState() != Square::State::IS_FREE)
	{
		startSquare.setPreviousState(Square::State::IS_FREE);
	}
	if (isMockingMove)
		square.saveCurrentState();

	if (Colors::isBlack(m_Color))
		square.setState(Square::State::HAS_BLACK_PIECE);
	if (Colors::isWhite(m_Color))
		square.setState(Square::State::HAS_WHITE_PIECE);
}

void Piece::clearLegalSquares()
{
	m_LegalSquaresIds.clear();
}

void Piece::addLegalSquare(int squareId)
{
	m_LegalSquaresIds.push_back(squareId);
}

void Piece::displayLegalMoves() const
{
	std::vector<Square*> legalSquares = GameManager::getInstance().getGameObjects<Square>(m_LegalSquaresIds);
	for (const auto& square : legalSquares)
		square->displayLegalMove();
}

void Piece::hideLegalMoves() const
{
	std::vector<Square*> legalSquares = GameManager::getInstance().getGameObjects<Square>(m_LegalSquaresIds);
	for (const auto& square : legalSquares)
		square->hideLegalMove();
}

bool Piece::findLegalSquare(const Square& square) const
{
	auto squareIterator = std::find_if(m_LegalSquaresIds.begin(), m_LegalSquaresIds.end(), [&square](int squareId)
	{
		return square == squareId;
	});
	return squareIterator != m_LegalSquaresIds.end();
}

bool Piece::hasNoLegalSquares() const
{
	return m_LegalSquaresIds.empty();
}

void Piece::attachMoveValidator(MoveValidator* moveValidator)
{
	m_MoveValidator = moveValidator;
}

void Piece::setSquare(const Square& square)
{
	m_SquareId = square.getId();
	m_PieceSprite.setPosition(square.getPosition());
}

void Piece::attachLineValidator(ILineValidator* lineValidator)
{
	m_LineValidator = lineValidator;
}

void Piece::move(Square& square, bool isMockingMove)
{
	updateSquareState(square, isMockingMove);
	setSquare(square);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_PieceSprite, states);
}

bool Piece::isLegalMove(Square& square)
{
	return !square.hasAllyPiece(m_Color);
}

bool Piece::isTriggered(const sf::Vector2i& mousePosition) const
{
	return m_PieceSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition));
}

void Piece::setOpacity(sf::Uint8 opacity)
{
	m_PieceSprite.setColor(sf::Color(255, 255, 255, opacity));
}

Piece::~Piece()
{
}
