#pragma once
#include "Piece.h"


class Rook : public Piece
{
public:
	Rook(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color);
	virtual bool isLegalMove(const Square& square) override;
	~Rook();
};

