#include "pch.h"
#include "Square.h"
#include "Colors.h"
#include "GameManager.h"

Square::Square()
{
}

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
	this->m_PreviousState = State::IS_FREE;

	initializeSquareShape();
	initializeLegalCaptureShape();
	initializeLegalMoveShape();
	initializeCheckShape();
}

void Square::initializeSquareShape()
{
	m_Shape.setFillColor(m_Color);
	m_Shape.setSize(sf::Vector2f(m_Size, m_Size));
	m_Shape.setOrigin(m_Shape.getLocalBounds().width / 2, m_Shape.getLocalBounds().height / 2);
	m_Shape.setPosition(m_Position);
}

void Square::initializeLegalCaptureShape()
{
	for (int i = 0; i < 4; i++)
	{
		sf::VertexArray triangle(sf::Triangles, 3);
		const sf::Color& green = Colors::getColor(Colors::Names::GREEN);
		const sf::Vector2f& squareCenter = m_Position;
		float halfSquareSide = m_Shape.getLocalBounds().width / 2;
		float quarterSquareSide = halfSquareSide / 2;

		triangle[0].color = green;
		triangle[1].color = green;
		triangle[2].color = green;

		sf::Vector2f topLeftPoint(squareCenter.x - halfSquareSide, squareCenter.y - halfSquareSide);
		sf::Vector2f bottomLeftPoint(squareCenter.x + halfSquareSide, squareCenter.y - halfSquareSide);
		sf::Vector2f topRightPoint(squareCenter.x - halfSquareSide, squareCenter.y + halfSquareSide);
		sf::Vector2f bottomRightPoint(squareCenter.x + halfSquareSide, squareCenter.y + halfSquareSide);

		switch (i)
		{
		case 0:
			triangle[0].position = topLeftPoint;
			triangle[1].position = sf::Vector2f(topLeftPoint.x + quarterSquareSide, topLeftPoint.y);
			triangle[2].position = sf::Vector2f(topLeftPoint.x, topLeftPoint.y + quarterSquareSide);
			break;
		case 1:
			triangle[0].position = bottomLeftPoint;
			triangle[1].position = sf::Vector2f(bottomLeftPoint.x - quarterSquareSide, bottomLeftPoint.y);
			triangle[2].position = sf::Vector2f(bottomLeftPoint.x, bottomLeftPoint.y + quarterSquareSide);
			break;
		case 2:
			triangle[0].position = bottomRightPoint;
			triangle[1].position = sf::Vector2f(bottomRightPoint.x - quarterSquareSide, bottomRightPoint.y);
			triangle[2].position = sf::Vector2f(bottomRightPoint.x, bottomRightPoint.y - quarterSquareSide);
			break;
		case 3:
			triangle[0].position = topRightPoint;
			triangle[1].position = sf::Vector2f(topRightPoint.x + quarterSquareSide, topRightPoint.y);
			triangle[2].position = sf::Vector2f(topRightPoint.x, topRightPoint.y - quarterSquareSide);
			break;
		}
		m_LegalCaptureShapes.push_back(std::move(triangle));
	}
}

void Square::initializeLegalMoveShape()
{
	m_LegalMoveShape.setFillColor(Colors::getColor(Colors::Names::GREEN));
	m_LegalMoveShape.setRadius(m_Shape.getLocalBounds().width / 8);
	m_LegalMoveShape.setOrigin(m_LegalMoveShape.getLocalBounds().width / 2, m_LegalMoveShape.getLocalBounds().height / 2);
	m_LegalMoveShape.setPosition(m_Position);
	m_LegalMoveShape.setOutlineColor(sf::Color::Black);
	m_LegalMoveShape.setOutlineThickness(2);
}

void Square::initializeCheckShape()
{
	m_CheckShape.setFillColor(Colors::getColor(Colors::Names::RED));
	m_CheckShape.setRadius(m_Shape.getLocalBounds().width / 2);
	m_CheckShape.setOrigin(m_CheckShape.getLocalBounds().width / 2, m_CheckShape.getLocalBounds().height / 2);
	m_CheckShape.setPosition(m_Position);
}

void Square::resetColor()
{
	m_Color = getInitialColor();
	m_Shape.setFillColor(m_Color);
}

void Square::setDisplayCheck(bool isDisplayed)
{
	m_CheckShapeIsDisplayed = isDisplayed;
}

void Square::displayLegalMove()
{
	if (isFree())
		m_LegalMoveShapeIsDisplayed = true;
	else
		m_LegalCaptureShapeIsDisplayed = true;
}

void Square::hideLegalMove()
{
	m_LegalCaptureShapeIsDisplayed = false;
	m_LegalMoveShapeIsDisplayed = false;
}

void Square::setColor(const sf::Color& color)
{
	m_Color = color;
	m_Shape.setFillColor(color);
}

void Square::setOpacity(sf::Uint8 opacity)
{
	m_Color = std::move(sf::Color(m_Color.r, m_Color.g, m_Color.b, opacity));
	m_Shape.setFillColor(m_Color);
}

void Square::setState(const State& state)
{
	m_State = state;
}

void Square::saveCurrentState()
{
	m_PreviousState = m_State;
}

void Square::restoreState()
{
	m_State = m_PreviousState;
}

void Square::setPreviousState(const State& state)
{
	m_PreviousState = state;
}

const Square::State& Square::getPreviousState() const
{
	return m_PreviousState;
}

bool Square::isFree() const
{
	return m_State == State::IS_FREE;
}

bool Square::hasAllyPiece(const sf::Color& color) const
{
	if (isFree())
		return false;

	const sf::Color& blackColor = Colors::getColor(Colors::Names::BLACK);
	const sf::Color& whiteColor = Colors::getColor(Colors::Names::WHITE);
	return (m_State == State::HAS_BLACK_PIECE && color == blackColor) ||
		   (m_State == State::HAS_WHITE_PIECE && color == whiteColor);
}

bool Square::hasEnemyPiece(const sf::Color& color) const
{
	if (isFree())
		return false;

	const sf::Color& blackColor = Colors::getColor(Colors::Names::BLACK);
	const sf::Color& whiteColor = Colors::getColor(Colors::Names::WHITE);
	return (m_State == State::HAS_BLACK_PIECE && color == whiteColor) ||
		   (m_State == State::HAS_WHITE_PIECE && color == blackColor);
}

const sf::Color& Square::getColor() const
{
	return m_Color;
}

const sf::Color& Square::getInitialColor() const
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
	if (m_CheckShapeIsDisplayed)
		target.draw(m_CheckShape, states);
	if (m_LegalMoveShapeIsDisplayed)
		target.draw(m_LegalMoveShape, states);
	if (m_LegalCaptureShapeIsDisplayed)
	{
		for (const auto& triangle : m_LegalCaptureShapes)
			target.draw(triangle, states);
	}
}

bool Square::isTriggered(const sf::Vector2i& mousePosition) const
{
	return m_Shape.getGlobalBounds().contains(sf::Vector2f(mousePosition));
}

Square::~Square()
{
}
