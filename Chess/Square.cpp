#include "pch.h"
#include "Square.h"
#include "ChessGame.h"

Square::Square()
{}

Square::Square(const sf::Color& color,
	const sf::Vector2i& coordinates,
	const sf::Vector2f& position,
	std::unique_ptr<Piece> piece,
	double size,
	bool free,
	int timesAttacked)
{
	this->m_Piece = std::move(piece);
	piece = nullptr;

	this->m_Color = color;
	this->m_Coordinates = coordinates;
	this->m_Position = position;
	this->m_Size = size;
	this->m_Free = free;
	this->m_TimesAttacked = timesAttacked;

	m_Shape.setFillColor(m_Color);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Position);
	m_Shape.setSize(sf::Vector2f(m_Size, m_Size));
}

Square::Square(Square&& square)
{
	this->m_Piece = std::move(square.m_Piece);
	square.m_Piece = nullptr;

	this->m_Shape = square.m_Shape;
	this->m_Color = square.m_Color;
	this->m_Coordinates = square.m_Coordinates;
	this->m_Position = square.m_Position;
	this->m_Size = square.m_Size;
	this->m_Free = square.m_Free;
	this->m_TimesAttacked = square.m_TimesAttacked;
}

Square& Square::operator=(Square&& square)
{
	// Self-assignment detection
	if (&square == this)
		return *this;

	m_Piece.release();

	this->m_Piece = std::move(square.m_Piece);
	square.m_Piece = nullptr;

	this->m_Shape = square.m_Shape;
	this->m_Color = square.m_Color;
	this->m_Coordinates = square.m_Coordinates;
	this->m_Position = square.m_Position;
	this->m_Size = square.m_Size;
	this->m_Free = square.m_Free;
	this->m_TimesAttacked = square.m_TimesAttacked;

	return *this;
}

const sf::Color& Square::getColor() const
{
	return m_Color;
}

const sf::Vector2i& Square::getCoordinates() const
{
	return m_Coordinates;
}

const sf::Vector2f& Square::getPosition() const
{
	return m_Position;
}

Piece* Square::getPiece() const
{
	return m_Piece.get();
}

void Square::setPiece(std::unique_ptr<Piece> piece)
{
	m_Piece = std::move(piece);
}

void Square::movePiece(Square& square)
{
	m_Piece->move(square);

	//If a piece is captured, delete it from everywhere
	if (square.getPiece() != nullptr)
		ChessGame::getInstance().removeDrawableObject(square.getPiece());

	//Assign the square a new piece
	square.setPiece(std::move(m_Piece));
}

bool Square::isFree() const
{
	return m_Free;
}

bool Square::isFreeForKing() const
{
	if (m_TimesAttacked > 0)
		return false;
	else if (m_TimesAttacked == 0)
		return true;
	return false;
}

void Square::increaseTimesAttacked()
{
	++m_TimesAttacked;
}

void Square::decreaseTimesAttacked()
{
	if (m_TimesAttacked != 0)
		--m_TimesAttacked;
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape, states);
}

bool Square::isTriggered(const sf::Vector2i& mousePosition) const
{
	//If the mouse is inside the square, return true (false otherwise)
	if (m_Shape.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
		return true;
	return false;
}

Square::~Square()
{
}
