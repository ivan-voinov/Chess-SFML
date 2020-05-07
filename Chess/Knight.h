#pragma once
#include "Piece.h"


class Knight : public Piece
{
public:
	Knight(const sf::Vector2f& position, const sf::Color& color);
	Knight(const sf::Vector2f& position, int squareId, const sf::Color& color);
	void onSuccessfulMove() override;
	bool controlsSquare(const Square& square) const override;
	bool isLegalMove(Square& square) override;
	~Knight();
};

