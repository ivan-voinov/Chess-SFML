#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"

class Square;

class Piece : public sf::Drawable
{
protected:
	sf::Vector2i m_Coordinates;
	sf::Texture m_PieceTexture;
	sf::Sprite m_PieceSprite;
	sf::Color m_Color;
public:
	Piece(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color);
	const sf::Color& getColor() const;
	bool canBeCaptured(const Piece &piece) const;
	void move(Square& square);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool isLegalMove(const Square& square) = 0;
	~Piece();
};

