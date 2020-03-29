#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "Colors.h"
#include "GameObject.h"

class Square : public ITriggered, public GameObject
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
	sf::Color m_Color;
	sf::Vector2i m_Coordinates;
	sf::Vector2f m_Position;
	State m_State;
	double m_Size;

public:
	Square();
	Square(const sf::Color& color,
		const sf::Vector2i& coordinates,
		const sf::Vector2f& position,
		double size,
		const State& state
		);
	Square(Square&& square);
	Square& operator=(Square&& square);
	void resetColor();
	void setColor(const sf::Color& color);
	void setState(const State& state);
	bool isFree() const;
	bool hasAllyPiece(const sf::Color& color) const;
	bool hasEnemyPiece(const sf::Color& color) const;
	sf::Color getColor() const;
	sf::Color getInitialColor() const;
	const sf::Vector2i& getCoordinates() const;
	const sf::Vector2f& getPosition() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	~Square();
};

