#pragma once
#include "Piece.h"


class Bishop : public Piece
{
public:
	Bishop(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color);
	virtual void move(const sf::Vector2f& position);
	virtual bool isLegalMove(const Square& square);
	~Bishop();
};

