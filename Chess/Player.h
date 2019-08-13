#pragma once
#include "SFML/Graphics.hpp"
#include "Square.h"
#include "Collection.h"

class Board;

class Player : public Collection
{
private:
	Square* m_FocusedPiece = nullptr;
	Board* m_Board;
	std::vector<Square*> m_Pieces;
	bool m_IsPlayerTurn;
	sf::Color m_PlayerColor;

public:
	Player(const sf::Color& playerColor);
	void addPiece(Square* square);
	void choosePiece(const sf::Vector2i& mousePosition);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	void setBoard(Board* board);
	bool makeMove();
	void endTurn();
	void startTurn();
	void resetFocusedPiece();
	virtual void removeGameObject(GameObject* gameObject) override;
	~Player();
};

