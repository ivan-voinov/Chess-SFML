#include "pch.h"
#include "Square.h"
#include "GameManager.h"

Square::Square()
{}

Square::Square(const sf::Color& color,
	const sf::Vector2i& coordinates,
	const sf::Vector2f& position,
	double size
	)
{
	this->m_Color = color;
	this->m_Coordinates = coordinates;
	this->m_Position = position;
	this->m_Size = size;

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

	return *this;
}

void Square::resetColor()
{
	m_Color = getInitialColor();
	m_Shape.setFillColor(m_Color);
}

void Square::setColor(sf::Color color)
{
	m_Color = color;
	m_Shape.setFillColor(color);
}

sf::Color Square::getColor() const
{
	return m_Color;
}

sf::Color Square::getInitialColor() const
{
	if ((m_Coordinates.x % 2 == 0) && (m_Coordinates.y % 2 == 0) ||
		(m_Coordinates.x % 2 == 1) && (m_Coordinates.y % 2 == 1))
			return Colors::getInstance().getColor(Colors::ColorNames::LIGHT_BROWN);
	else
		return Colors::getInstance().getColor(Colors::ColorNames::DARK_BROWN);
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
	//If the mouse is inside the square, return true (false otherwise)
	return m_Shape.getGlobalBounds().contains(sf::Vector2f(mousePosition)) ? true : false;
}

Square::~Square()
{
}
