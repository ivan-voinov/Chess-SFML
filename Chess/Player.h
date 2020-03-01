#pragma once
#include "SFML/Graphics.hpp"
#include "Colors.h"

class Board;
class Square;
class Piece;

class Player
{
private:
	int m_FocusedPieceId = -1;
	std::vector<int> m_PiecesIds;
	bool m_IsPlayerTurn;
	sf::Color m_PlayerColor;

public:
	Player(const sf::Color& playerColor);
	void addPiece(int pieceId);
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

