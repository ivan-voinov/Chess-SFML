#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color);
	virtual bool isLegalMove(const Square& square) override;
	~King();
};

