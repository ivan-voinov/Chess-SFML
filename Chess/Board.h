#pragma once
#include <SFML/Graphics.hpp>
#include "ILineValidator.h"

class Square;
class Player;
class Piece;

class Board : public ILineValidator
{
private:
	static constexpr int m_BoardSize = 8;
	static constexpr double m_SquareSize = 55;
	std::vector<int> m_SquareIds;

	const sf::Color& getStartSquareColor(const sf::Vector2i& squareCoords) const;
	void addSquare(const sf::Vector2i& coords, const sf::Vector2f& pos, const sf::Color& color);
	void swapCoordinates(sf::Vector2i& coords1, sf::Vector2i& coords2) const;
	std::unique_ptr<Piece> getStartSquarePiece(const Square& square) const;

public:
	Board();
	static const double getSquareSize();
	Square* getSquare(const sf::Vector2i coords) const;
	Square* getTriggeredSquare(const sf::Vector2i& mousePosition);
	void setOpacity(sf::Uint8 opacity) const;
	bool diagonalIsFree(const Square& startSquare, const Square& destSquare) const override;
	bool LineIsFree(const Square& startSquare, const Square& destSquare) const override;
	void buildBoard(const sf::RenderWindow& window);
	void assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer);
	~Board();
};

