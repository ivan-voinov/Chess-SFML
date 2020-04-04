#pragma once
#include "SFML/Graphics.hpp"
#include "Colors.h"
#include "IObserver.h"

class Board;
class Square;
class Piece;
class Rook;

class Player : public IObserver
{
private:
	Player* m_Opponent = nullptr;
	int m_FocusedPieceId = -1;
	int m_KingId = -1;
	std::vector<int> m_PiecesIds;
	bool m_IsPlayerTurn;
	bool m_Checked = false;
	sf::Color m_PlayerColor;
	virtual void update(const std::string& event, Square& square, const Board& board) override;
	bool castlingIsLegal(
		Square& square,
		const Board& board,
		Piece& focusedPiece,
		Rook* rook,
		const sf::Vector2i attackedSquareCoords);

public:
	Player(const sf::Color& playerColor);
	void addPiece(int pieceId);
	Piece* getTriggeredPiece(const sf::Vector2i& mousePosition);
	Piece* findPiece(const Square& square) const;
	Piece* getKing() const;
	void attachOpponent(Player& opponent);
	void setKing(int kingId);
	void checkKing();
	void uncheckKing();
	void removePiece(int capturedPieceId);
	bool isChecked(const Board& board) const;
	bool controlsSquare(Square& square, const Board& board);
	void resizePieces(const double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	bool makeMove(Square& square, const Board& board, Piece& focusedPiece);
	void onSuccessfulMove(Square& square, Piece& piece);
	void onFailedMove(Square& square);
	void processTurn(Board& board, sf::RenderWindow& window);
	void choosePiece(const Board& board, Piece& triggeredPiece);
	void switchTurn();
	void resetMoveState(Square& square);
	void highlightSquare(Square& square);
	~Player();
};

