#pragma once
#include "Piece.h"


class Bishop : public Piece
{
private:
	std::vector<Square*> m_AttackedSquares;
public:
	Bishop(const sf::Vector2f& position, const sf::Color& color);
	virtual void move(const sf::Vector2f& position);
	virtual bool isLegalMove(const Square& square);
	~Bishop();
};

