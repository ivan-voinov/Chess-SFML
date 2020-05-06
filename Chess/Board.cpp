#include "pch.h"
#include "Board.h"
#include "PieceHeaders.h"
#include "GameManager.h"
#include "SquareBuilder.h"
#include "Colors.h"

#define MAX_X 8

Board::Board()
{
}

const sf::Color& Board::getStartSquareColor(const sf::Vector2i& squareCoords) const
{
	int x = squareCoords.x;
	int y = squareCoords.y;

	return (x % 2 == 0 && y % 2 == 0 || x % 2 != 0 && y % 2 != 0) ? Colors::getColor(Colors::Names::LIGHT_BROWN) : 
		Colors::getColor(Colors::Names::DARK_BROWN);
}

const double Board::getSquareSize()
{
	return m_SquareSize;
}

Square* Board::getSquare(const sf::Vector2i coords) const
{
	int squareId = coords.x * MAX_X + coords.y;
	return GameManager::getInstance().getGameObject<Square>(m_SquareIds.at(squareId));
}

Square* Board::getTriggeredSquare(const sf::Vector2i& mousePosition)
{
	std::vector<Square*> squares = GameManager::getInstance().getGameObjects<Square>(m_SquareIds);
	for (auto& square : squares)
	{
		if (square->isTriggered(mousePosition))
			return square;
	}
	return nullptr;
}

void Board::setOpacity(sf::Uint8 opacity) const
{
	std::vector<Square*> squares = GameManager::getInstance().getGameObjects<Square>(m_SquareIds);
	for (auto& square : squares)
		square->setOpacity(opacity);
}

void Board::swapCoordinates(sf::Vector2i& coords1, sf::Vector2i& coords2) const
{
	sf::Vector2i temp = coords1;
	coords1 = coords2;
	coords2 = temp;
}

bool Board::LineIsFree(const Square& startSquare, const Square& destSquare) const
{
	sf::Vector2i startPoint(startSquare.getCoordinates());
	sf::Vector2i endPoint(destSquare.getCoordinates());
	int xDifference = abs(startPoint.x - endPoint.x);
	int yDifference = abs(startPoint.y - endPoint.y);
	bool isVertical = false;

	if (!((xDifference == 0 && yDifference > 0) || (yDifference == 0 && xDifference > 0)))
	{
		return false;
	}
	if (startPoint.x < endPoint.x && startPoint.y == endPoint.y)
	{
		isVertical = true;
	}
	if (startPoint.x > endPoint.x && startPoint.y == endPoint.y)
	{
		isVertical = true;
		swapCoordinates(startPoint, endPoint);
	}
	if (startPoint.x == endPoint.x && startPoint.y < endPoint.y)
	{
		isVertical = false;
	}
	if (startPoint.x == endPoint.x && startPoint.y > endPoint.y)
	{
		isVertical = false;
		swapCoordinates(startPoint, endPoint);
	}
	int i = isVertical ? startPoint.x + 1 : startPoint.x;
	int j = isVertical ? startPoint.y : startPoint.y + 1;
	if (isVertical)
	{
		for (i; i < endPoint.x; i++)
			if (!getSquare(sf::Vector2i(i, j))->isFree())
				return false;
	}
	else
	{
		for (j; j < endPoint.y; j++)
			if (!getSquare(sf::Vector2i(i, j))->isFree())
				return false;
	}
	return true;
}

bool Board::diagonalIsFree(const Square& startSquare, const Square& destSquare) const
{
	bool isMainDiagonal = false;
	sf::Vector2i startPoint(startSquare.getCoordinates());
	sf::Vector2i endPoint(destSquare.getCoordinates());
	int xDifference = abs(startPoint.x - endPoint.x);
	int yDifference = abs(startPoint.y - endPoint.y);

	if ((xDifference != yDifference) || xDifference == 0)
	{
		return false;
	}
	if (startPoint.x < endPoint.x && startPoint.y < endPoint.y)
	{
		isMainDiagonal = true;
	}
	if (startPoint.x > endPoint.x && startPoint.y > endPoint.y)
	{
		isMainDiagonal = true;
		swapCoordinates(startPoint, endPoint);
	}
	if (startPoint.x < endPoint.x && startPoint.y > endPoint.y)
	{
		isMainDiagonal = false;
	}
	if (startPoint.x > endPoint.x && startPoint.y < endPoint.y)
	{
		isMainDiagonal = false;
		swapCoordinates(startPoint, endPoint);
	}

	int j = startPoint.y;
	for (int i = startPoint.x + 1; i < endPoint.x; i++)
	{
		j = isMainDiagonal ? (j + 1) : (j - 1);
		if (!getSquare(sf::Vector2i(i, j))->isFree())
			return false;
	}
	return true;
}

//Build the pieces and assign them to players
void Board::assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer)
{
	std::vector<Square*> board = GameManager::getInstance().getGameObjects<Square>(m_SquareIds);
	for (const auto& square : board)
	{
		//Build the piece
		std::unique_ptr<Piece> piece = getStartSquarePiece(*square);

		//If built successfully, give it a reference to it's square and assign to a player
		if (piece)
		{
			//If the piece is white, assign it to white player
			if (Colors::isWhite(piece->getColor()))
			{
				whitePlayer.addPiece(piece->getId());
				square->setState(Square::State::HAS_WHITE_PIECE);
				if (square->getCoordinates().x == 7 && square->getCoordinates().y == 4)
					whitePlayer.setKing(piece->getId());
			}
			//If the piece is black, assign it to black player
			else if (Colors::isBlack(piece->getColor()))
			{
				blackPlayer.addPiece(piece->getId());
				square->setState(Square::State::HAS_BLACK_PIECE);
				if (square->getCoordinates().x == 0 && square->getCoordinates().y == 4)
					blackPlayer.setKing(piece->getId());
			}
			GameManager::getInstance().addGameObject(std::move(piece));
		}
	}
}

//Return the correct piece for the square at the start of the game
std::unique_ptr<Piece> Board::getStartSquarePiece(const Square& square) const
{
	const sf::Vector2f& squarePosition = square.getPosition();
	const sf::Vector2i& squareCoordinates = square.getCoordinates();
	int squareId = square.getId();

	//Return black pawn
	if (squareCoordinates.x == 1)
		return std::make_unique<Pawn>(squarePosition, squareId, Colors::getColor(Colors::Names::BLACK));

	//Return white pawn
	if (squareCoordinates.x == 6)
		return std::make_unique<Pawn>(squarePosition, squareId, Colors::getColor(Colors::Names::WHITE));

	//Return black rook
	if (squareCoordinates == sf::Vector2i(0, 0) || squareCoordinates == sf::Vector2i(0, 7))
		return std::make_unique<Rook>(squarePosition, squareId, Colors::getColor(Colors::Names::BLACK));

	//Return white rook
	if (squareCoordinates == sf::Vector2i(7, 0) || squareCoordinates == sf::Vector2i(7, 7))
		return std::make_unique<Rook>(squarePosition, squareId, Colors::getColor(Colors::Names::WHITE));

	//Return black knight
	if (squareCoordinates == sf::Vector2i(0, 1) || squareCoordinates == sf::Vector2i(0, 6))
		return std::make_unique<Knight>(squarePosition, squareId, Colors::getColor(Colors::Names::BLACK));

	//Return white knight
	if (squareCoordinates == sf::Vector2i(7, 1) || squareCoordinates == sf::Vector2i(7, 6))
		return std::make_unique<Knight>(squarePosition, squareId, Colors::getColor(Colors::Names::WHITE));

	//Return black bishop
	if (squareCoordinates == sf::Vector2i(0, 2) || squareCoordinates == sf::Vector2i(0, 5))
		return std::make_unique<Bishop>(squarePosition, squareId, Colors::getColor(Colors::Names::BLACK));

	//Return white bishop
	if (squareCoordinates == sf::Vector2i(7, 2) || squareCoordinates == sf::Vector2i(7, 5))
		return std::make_unique<Bishop>(squarePosition, squareId, Colors::getColor(Colors::Names::WHITE));

	//Return black queen
	if (squareCoordinates == sf::Vector2i(0, 3))
		return std::make_unique<Queen>(squarePosition, squareId, Colors::getColor(Colors::Names::BLACK));

	//Return white queen
	if (squareCoordinates == sf::Vector2i(7, 3))
		return std::make_unique<Queen>(squarePosition, squareId, Colors::getColor(Colors::Names::WHITE));

	//Return black king
	if (squareCoordinates == sf::Vector2i(0, 4))
		return std::make_unique<King>(squarePosition, squareId, Colors::getColor(Colors::Names::BLACK));

	//Return white king
	if (squareCoordinates == sf::Vector2i(7, 4))
		return std::make_unique<King>(squarePosition, squareId, Colors::getColor(Colors::Names::WHITE));

	return nullptr;
}

void Board::buildBoard(const sf::RenderWindow& window)
{
	//Build white-black rows
	for (int i = 0; i < m_BoardSize; ++i)
	{
		for (int j = 0; j < m_BoardSize; ++j)
		{
			sf::Vector2f squarePosition =
				std::move(sf::Vector2f(window.getSize().x / 4 + j * m_SquareSize, window.getSize().y / 4 + i * m_SquareSize));
			sf::Vector2i squareCoordinates = std::move(sf::Vector2i(i, j));

			const sf::Color& squareColor = getStartSquareColor(std::move(sf::Vector2i(i, j)));
			addSquare(squareCoordinates, squarePosition, squareColor);
		}
	}
}

void Board::addSquare(const sf::Vector2i& coords, const sf::Vector2f& pos, const sf::Color& color)
{
	std::unique_ptr<Square> newSquare = std::move(std::make_unique<Square>(SquareBuilder(coords, m_SquareSize)
			.color(color)
			.position(pos)
			.state(Square::State::IS_FREE)
			.build()));
	m_SquareIds.push_back(newSquare->getId());
	GameManager::getInstance().addGameObject(std::move(newSquare));
}

Board::~Board()
{
}
