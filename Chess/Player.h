#pragma once
#include "SFML/Graphics.hpp"
#include "Square.h"

class Player
{
private:
	Square* m_ActivePiece;
	std::vector<Square*> m_Pieces;
public:
	Player();
	void addPiece(Square* square);
	void removePiece(Square* square);
	bool choosePiece(const sf::Vector2i& mousePosition);
	~Player();
};

