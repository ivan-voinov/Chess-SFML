#include "pch.h"
#include "Square.h"
#include "GameManager.h"

Square::Square()
{}

Square::Square(const sf::Color& color,
	const sf::Vector2i& coordinates,
	const sf::Vector2f& position,
	double size,
	const State& state
	)
{
	this->m_Color = color;
	this->m_Coordinates = coordinates;
	this->m_Position = position;
	this->m_Size = size;
	this->m_State = state;

	m_Shape.setFillColor(m_Color);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Position);
	m_Shape.setSize(sf::Vector2f(m_Size, m_Size));
}

Square::Square(Square&& square)
{
	this->m_Shape = square.m_Shape;
	this->m_Color = square.m_Color;
	this->m_Coordinates = square.m_Coordinates;
	this->m_Position = square.m_Position;
	this->m_Size = square.m_Size;
	this->m_State = square.m_State;
}

Square& Square::operator=(Square&& square)
{
	// Self-assignment detection
	if (&square == this)
		return *this;

	this->m_Shape = square.m_Shape;
	this->m_Color = square.m_Color;
	this->m_Coordinates = square.m_Coordinates;
	this->m_Position = square.m_Position;
	this->m_Size = square.m_Size;
	this->m_State = square.m_State;

	return *this;
}

void Square::resetColor()
{
	m_Color = getInitialColor();
	m_Shape.setFillColor(m_Color);
}

void Square::setColor(const sf::Color& color)
{
	m_Color = color;
	m_Shape.setFillColor(color);
}

void Square::setState(const State& state)
{
	m_State = state;
}

bool Square::isFree() const
{
	return m_State == State::IS_FREE;
}

bool Square::hasAllyPiece(const sf::Color& color) const
{
	if (isFree())
		return false;

	sf::Color blackColor = Colors::getColor(Colors::Names::BLACK);
	sf::Color whiteColor = Colors::getColor(Colors::Names::WHITE);
	return (m_State == State::HAS_BLACK_PIECE && color == blackColor) ||
		   (m_State == State::HAS_WHITE_PIECE && color == whiteColor);
}

bool Square::hasEnemyPiece(const sf::Color& color) const
{
	if (isFree())
		return false;

	sf::Color blackColor = Colors::getColor(Colors::Names::BLACK);
	sf::Color whiteColor = Colors::getColor(Colors::Names::WHITE);
	return (m_State == State::HAS_BLACK_PIECE && color == whiteColor) ||
		   (m_State == State::HAS_WHITE_PIECE && color == blackColor);
}

sf::Color Square::getColor() const
{
	return m_Color;
}

sf::Color Square::getInitialColor() const
{
	if ((m_Coordinates.x % 2 == 0) && (m_Coordinates.y % 2 == 0) ||
		(m_Coordinates.x % 2 == 1) && (m_Coordinates.y % 2 == 1))
			return Colors::getColor(Colors::Names::LIGHT_BROWN);
	else
		return Colors::getColor(Colors::Names::DARK_BROWN);
}

const sf::Vector2i& Square::getCoordinates() const
{
	return m_Coordinates;
}

const sf::Vector2f& Square::getPosition() const
{
	return m_Position;
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape, states);
}

bool Square::isTriggered(const sf::Vector2i& mousePosition) const
{
	return m_Shape.getGlobalBounds().contains(sf::Vector2f(mousePosition));
}

Square::~Square()
{
}
