#pragma once
#include "SFML/Graphics.hpp"
#include "Colors.h"

class Board;

class Player
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
	void choosePiece(const sf::Vector2i& mousePosition);
	Piece* findPieceBySquare(const Square& square) const;
	void resizePieces(const double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	bool isLegalMove(Square& square) const;
	void makeMove(Square& square);
	void processTurn(Player& opponent, Board& board, sf::RenderWindow& window);
	void switchTurn(Player& opponent);
	void resetFocusedPiece();
	void resetFocusedPieceColor();
	~Player();
};

