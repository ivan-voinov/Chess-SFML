#include "pch.h"
#include "Piece.h"
#include "Square.h"
#include "GameManager.h"


Piece::Piece(const sf::Vector2f& position, const sf::Color& color)
{
	this->m_Color = color;

	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setPosition(position);
}

const sf::Color& Piece::getColor() const
{
	return m_Color;
}

void Piece::setSquare(int squareId)
{
	m_SquareId = squareId;
}

Square* Piece::getSquare() const
{
	return GameManager::getInstance().getGameObject<Square>(m_SquareId);
}

void Piece::move(Square& square)
{
	updateSquareState(square);
	m_SquareId = square.getId();
	m_PieceSprite.setPosition(square.getPosition());
}

void Piece::resize(const double squareSize)
{
	m_PieceSprite.setScale(squareSize / m_PieceTexture.getSize().x, squareSize / m_PieceTexture.getSize().y);
}

void Piece::updateSquareState(Square& square)
{
	sf::Color blackColor = Colors::getColor(Colors::Names::BLACK);
	sf::Color whiteColor = Colors::getColor(Colors::Names::WHITE);
	Square& startSquare = *getSquare();

	startSquare.setState(Square::State::IS_FREE);
	if (m_Color == blackColor)
		square.setState(Square::State::HAS_BLACK_PIECE);
	if (m_Color == whiteColor)
		square.setState(Square::State::HAS_WHITE_PIECE);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_PieceSprite, states);
}

bool Piece::isLegalMove(Square & square, const Board& board)
{
	return !square.hasAllyPiece(m_Color);
}

bool Piece::isTriggered(const sf::Vector2i& mousePosition) const
{
	return m_PieceSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) ? true : false;
}

void Piece::registerObserver(IObserver* observer)
{
	m_Observers.push_back(observer);
}

void Piece::removeObserver(IObserver* observer)
{

}

void Piece::notifyObserver(const std::string& event, Square& square, const Board& board) const
{
	for (const auto& observer : m_Observers)
	{
		observer->update(event, square, board);
	}
}

Piece::~Piece()
{
}
