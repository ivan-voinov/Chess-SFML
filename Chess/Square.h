#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "Piece.h"

class Square : public ITriggered, public GameObject
{
public:
	static const sf::Color whiteColor;
	static const sf::Color blackColor;
	static const sf::Color greenColor;
	static const sf::Color darkBrownColor;
	static const sf::Color lightBrownColor;

private:
	sf::RectangleShape m_Shape;
	sf::Color m_Color;
	sf::Vector2i m_Coordinates;
	sf::Vector2f m_Position;
	std::unique_ptr<Piece> m_Piece;

	double m_Size;
	bool m_Free;
	int m_TimesAttacked;

public:
	Square();
	Square(const sf::Color& color,
		const sf::Vector2i& coordinates,
		const sf::Vector2f& position,
		std::unique_ptr<Piece> piece,
		double size,
		bool free,
		int timesAttacked);
	Square(Square&& square);
	Square& operator=(Square&& square);
	void setColor(sf::Color color);
	sf::Color getColor() const;
	sf::Color getInitialColor() const;
	const sf::Vector2i& getCoordinates() const;
	const sf::Vector2f& getPosition() const;
	Piece* getPiece() const;
	void setPiece(std::unique_ptr<Piece> piece);
	void movePiece(Square& square);
	bool isFree() const;
	bool isFreeForKing() const;
	void increaseTimesAttacked();
	void decreaseTimesAttacked();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	~Square();
};

