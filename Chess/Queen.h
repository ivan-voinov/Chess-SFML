#pragma once
#include "Piece.h"


class Queen : public Piece
{
public:
	Queen(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color);
	virtual bool isLegalMove(const Square& square) override;
	~Queen();
};

