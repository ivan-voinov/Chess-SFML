#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "SquareBuilder.h"
#include "ObjectDrawer.h"

class Board
{
private:
	static constexpr int boardSize = 8;
	static constexpr double squareSize = 40;
	Square m_Board[boardSize][boardSize];
	Square* m_FocusedSquare = nullptr;

	void createEvenRows(const sf::RenderWindow& window, ObjectDrawer& objectDrawer);
	void createOddRows(const sf::RenderWindow& window, ObjectDrawer& objectDrawer);
public:
	Board();
	bool pieceIsChosen() const;
	void choosePiece(const sf::Vector2i& mousePosition);
	void chooseSquareForPiece(const sf::Vector2i& mousePosition);
	void readInput(const sf::Vector2i& mousePosition);
	void loadBoard(const sf::RenderWindow& window, ObjectDrawer& objectDrawer);
	std::unique_ptr<Piece> getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
		const sf::Vector2f& squarePosition) const;
	~Board();
};

