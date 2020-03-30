#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "SquareBuilder.h"
#include "Player.h"

class GameManager;

class Board
{
private:
	static constexpr int m_BoardSize = 8;
	static constexpr double m_SquareSize = 55;
	std::vector<int> m_SquareIds;

public:
	Board();
	static const double getSquareSize();
	Square* getSquare(const sf::Vector2i coords) const;
	Square* getTriggeredSquare(const sf::Vector2i& mousePosition);
	void swapCoordinates(sf::Vector2i& coords1, sf::Vector2i& coords2) const;
	bool diagonalIsFree(const Square& startSquare, const Square& destSquare) const;
	bool LineIsFree(const Square& startSquare, const Square& destSquare) const;
	void buildBoard(const sf::RenderWindow& window);
	void addSquare(const sf::Vector2i& coords, const sf::Vector2f& pos, const sf::Color& color);
	void assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer);
	std::unique_ptr<Piece> getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
		const sf::Vector2f& squarePosition) const;
	~Board();
};

