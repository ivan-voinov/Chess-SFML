#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "SquareBuilder.h"
#include "GameObjectContainer.h"
#include "Player.h"

class GameManager;

class Board
{
private:
	static constexpr int m_BoardSize = 8;
	static constexpr double m_SquareSize = 55;
	Square m_Board[m_BoardSize][m_BoardSize];
	Square* m_FocusedSquare;

	void createEvenRows(const sf::RenderWindow& window);
	void createOddRows(const sf::RenderWindow& window);
public:
	Board();
	static const double getSquareSize();
	bool chooseSquareForPiece(const sf::Vector2i& mousePosition);
	Square& getFocusedSquare();
	void resetFocusedSquare();
	bool squareIsChosen() const;
	void loadBoard(const sf::RenderWindow& window);
	void registerGameObjects();
	void assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer);
	
	std::unique_ptr<Piece> getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
		const sf::Vector2f& squarePosition) const;
	~Board();
};

