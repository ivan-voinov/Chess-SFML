#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "GameObject.h"


class Square;
class Player;

class Piece : public GameObject, public ITriggered
{
private:
	void swapCoordinates(sf::Vector2i& coords1, sf::Vector2i& coords2) const;

protected:
	int m_SquareId;
	sf::Texture m_PieceTexture;
	sf::Sprite m_PieceSprite;
	sf::Color m_Color;

	bool controlsDiagonal(
		const Player& player,
		const Player& opponent,
		const sf::Vector2i& coords1,
		const sf::Vector2i& coords2
	) const;

	bool controlsLine(
		const Player& player,
		const Player& opponent,
		const sf::Vector2i& coords1,
		const sf::Vector2i& coords2
	) const;

public:
	Piece(const sf::Vector2f& position, const sf::Color& color);
	const sf::Color& getColor() const;
	void setSquare(int squareId);
	Square* getSquare() const;
	void setSquareColor(const sf::Color& color);
	bool canBeCaptured(const Piece &piece) const;
	void move(Square& square);
	void resize(const double squareSize);
	void onCaptured();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool controlsSquare(const Square& square, const Player& player, const Player& opponent) const = 0;
	virtual bool isLegalMove(const Square& square, const Player& player, const Player& opponent);
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	~Piece();
};

