#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "SquareBuilder.h"

class ChessGame;

class Board
{
private:
	static constexpr int boardSize = 8;
	static constexpr double squareSize = 40;
	Square m_Board[boardSize][boardSize];
	Square* m_FocusedSquare = nullptr;

	void createEvenRows(const sf::RenderWindow& window);
	void createOddRows(const sf::RenderWindow& window);
public:
	Board();
	bool pieceIsChosen() const;
	void choosePiece(const sf::Vector2i& mousePosition);
	void chooseSquareForPiece(const sf::Vector2i& mousePosition);
	void readInput(const sf::Vector2i& mousePosition);
	void loadBoard(const sf::RenderWindow& window);
	std::unique_ptr<Piece> getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
		const sf::Vector2f& squarePosition) const;
	~Board();
};

