#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "GameObject.h"

class Square;

class Piece : public GameObject, public ITriggered
{
protected:
	Square* m_Square;
	sf::Texture m_PieceTexture;
	sf::Sprite m_PieceSprite;
	sf::Color m_Color;
	int numberOfPinningPieces = 0;
public:
	Piece(const sf::Vector2f& position, const sf::Color& color);
	const sf::Color& getColor() const;
	void setSquare(Square& square);
	Square* getSquare() const;
	void setSquareColor(const sf::Color& color);
	bool canBeCaptured(const Piece &piece) const;
	void move(Square& square);
	void resize(const double squareSize);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool isLegalMove(const Square& square) = 0;
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	~Piece();
};

