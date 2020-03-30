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
	int m_KingId = -1;
	std::vector<int> m_PiecesIds;
	bool m_IsPlayerTurn;
	bool m_Checked = false;
	sf::Color m_PlayerColor;

public:
	Player(const sf::Color& playerColor);
	void addPiece(int pieceId);
	Piece* getTriggeredPiece(const sf::Vector2i& mousePosition);
	Piece* findPiece(const Square& square) const;
	Piece* getKing() const;
	void setKing(int kingId);
	void checkKing();
	void uncheckKing();
	void removePiece(int capturedPieceId);
	bool isChecked(const Player& opponent, const Board& board) const;
	bool controlsSquare(const Square& square, const Board& board) const;
	void resizePieces(const double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	bool makeMove(Square& square, Player& opponent, const Board& board);
	void processTurn(Player& opponent, Board& board, sf::RenderWindow& window);
	void switchTurn(Player& opponent);
	void resetMoveState(Square& square);
	void highlightSquare(Square& square);
	~Player();
};

