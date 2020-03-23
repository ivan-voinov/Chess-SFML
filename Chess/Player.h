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
	int m_FocusedSquareId = -1;
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
	void resetFocusedSquare();
	void checkKing();
	void uncheckKing();
	void removePiece(int capturedPieceId, Player& opponent);
	bool squareIsChosen() const;
	bool isChecked(const Player& opponent) const;
	bool hasPieceOnSquare(const sf::Vector2i& squareCoordinates) const;
	bool controlsSquare(const Square& square, const Player& opponent) const;
	void resizePieces(const double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	void makeMove(Square& square, Player& opponent);
	void processTurn(Player& opponent, Board& board, sf::RenderWindow& window);
	void switchTurn(Player& opponent);
	void resetFocusedPiece();
	void resetFocusedPieceColor();
	void highlightFocusedPiece();
	~Player();
};

