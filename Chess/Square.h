#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "Piece.h"
#include "Colors.h"

class Square : public ITriggered, public GameObject
{
private:
	sf::RectangleShape m_Shape;
	sf::Color m_Color;
	sf::Vector2i m_Coordinates;
	sf::Vector2f m_Position;

	double m_Size;
	bool m_Free;

public:
	Square();
	Square(const sf::Color& color,
		const sf::Vector2i& coordinates,
		const sf::Vector2f& position,
		double size,
		bool free);
	Square(Square&& square);
	Square& operator=(Square&& square);
	void resetColor();
	void setColor(sf::Color color);
	sf::Color getColor() const;
	sf::Color getInitialColor() const;
	const sf::Vector2i& getCoordinates() const;
	const sf::Vector2f& getPosition() const;
	bool isFree() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	~Square();
};

