#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const sf::Vector2f& position, const sf::Color& color);
	Queen(const sf::Vector2f& position, int squareId, const sf::Color& color);
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square) const override;
	virtual bool isLegalMove(Square& square) override;
	~Queen();
};

