#pragma once
#include "Piece.h"


class Knight : public Piece
{
public:
	Knight(const sf::Vector2f& position, const sf::Color& color);
	virtual bool isLegalMove(const Square& square) override;
	~Knight();
};

