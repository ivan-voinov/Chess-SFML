#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "GameObject.h"
#include "IOpaque.h"

class Square : public GameObject, public ITriggered, public IOpaque
{
public:
	enum class State
	{
		HAS_WHITE_PIECE,
		HAS_BLACK_PIECE,
		IS_FREE
	};

private:
	sf::RectangleShape m_Shape;
	sf::CircleShape m_LegalMoveShape;
	sf::CircleShape m_CheckShape;
	std::vector<sf::VertexArray> m_LegalCaptureShapes;

	sf::Color m_Color;
	sf::Vector2i m_Coordinates;
	sf::Vector2f m_Position;
	State m_State;
	State m_PreviousState;
	float m_Size;

	bool m_CheckShapeIsDisplayed = false;
	bool m_LegalMoveShapeIsDisplayed = false;
	bool m_LegalCaptureShapeIsDisplayed = false;

	const sf::Color& getInitialColor() const;
	void initializeSquareShape();
	void initializeLegalCaptureShape();
	void initializeLegalMoveShape();
	void initializeCheckShape();

public:
	Square(const sf::Color& color,
		const sf::Vector2i& coordinates,
		const sf::Vector2f& position,
		float size,
		const State& state
		);
	void resetColor();
	void setDisplayCheck(bool isDisplayed);
	void displayLegalMove();
	void hideLegalMove();
	void setColor(const sf::Color& color);
	void setState(const State& state);
	void saveCurrentState();
	void restoreState();
	void setPreviousState(const State& state);
	const State& getPreviousState() const;
	bool isFree() const;
	bool hasAllyPiece(const sf::Color& color) const;
	bool hasEnemyPiece(const sf::Color& color) const;
	const sf::Color& getColor() const;
	const sf::Vector2i& getCoordinates() const;
	const sf::Vector2f& getPosition() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool isTriggered(const sf::Vector2i& mousePosition) const override;
	void setOpacity(sf::Uint8 opacity) override;
	~Square();
};

