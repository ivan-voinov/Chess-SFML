#pragma once
#include "SFML/Graphics.hpp"
#include "Square.h"
#include "Collection.h"
#include "Colors.h"

class Board;

class Player : public Collection
{
private:
	Piece* m_FocusedPiece = nullptr;
	std::vector<std::unique_ptr<Piece>> m_Pieces;
	bool m_IsPlayerTurn;
	sf::Color m_PlayerColor;

public:
	Player(const sf::Color& playerColor);
	void addPiece(std::unique_ptr<Piece> piece);
	void registerGameObjects();
	Piece* findPieceBySquare(const Square& square);
	void choosePiece(const sf::Vector2i& mousePosition);
	void resizePieces(const double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	bool isLegalMove(Square& square) const;
	void makeMove(Square& square);
	void endTurn();
	void startTurn();
	void resetFocusedPiece();
	virtual void removeGameObject(GameObject* gameObject) override;
	~Player();
};

