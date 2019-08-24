#include "pch.h"
#include "Board.h"
#include "Piece.h"
#include "PieceHeaders.h"
#include "GameManager.h"


Board::Board()
{
}

void Board::chooseSquareForPiece(const sf::Vector2i& mousePosition)
{
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			if (square.isTriggered(mousePosition))
			{
				m_FocusedSquare = &square;
			}
		}
	}
}

Square* Board::getFocusedSquare()
{
	return m_FocusedSquare;
}

void Board::resetFocusedSquare()
{
	m_FocusedSquare = nullptr;
}

bool Board::squareIsChosen() const
{
	if (m_FocusedSquare == nullptr)
		return false;
	return true;
}

void Board::loadBoard(const sf::RenderWindow& window)
{
	createOddRows(window);
	createEvenRows(window);
}

void Board::registerGameObjects()
{
	//Add squares
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			GameManager::getInstance().addGameObject(&square);
		}
	}
}

void Board::assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer)
{
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			std::unique_ptr<Piece> piece = 
				getStartingSquarePiece(m_Board[i][j].getCoordinates(), m_Board[i][j].getPosition());

			if (piece != nullptr)
			{
				piece.get()->setSquare(m_Board[i][j]);

				if (piece.get()->getColor() == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
				{
					whitePlayer.addPiece(std::move(piece));
				}
				else if (piece.get()->getColor() == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
				{
					blackPlayer.addPiece(std::move(piece));
				}
			}
		}
	}
}

std::unique_ptr<Piece> Board::getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
	const sf::Vector2f& squarePosition) const
{
	if (squareCoordinates.x == 1)
		return std::make_unique<Pawn>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	if (squareCoordinates.x == 6)
		return std::make_unique<Pawn>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	if (squareCoordinates == sf::Vector2i(0,0) || squareCoordinates == sf::Vector2i(0,7))
		return std::make_unique<Rook>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	if (squareCoordinates == sf::Vector2i(7,0) || squareCoordinates == sf::Vector2i(7,7))
		return std::make_unique<Rook>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	if (squareCoordinates == sf::Vector2i(0,1) || squareCoordinates == sf::Vector2i(0,6))
		return std::make_unique<Knight>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	if (squareCoordinates == sf::Vector2i(7,1) || squareCoordinates == sf::Vector2i(7,6))
		return std::make_unique<Knight>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	if (squareCoordinates == sf::Vector2i(0,2) || squareCoordinates == sf::Vector2i(0,5))
		return std::make_unique<Bishop>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	if (squareCoordinates == sf::Vector2i(7,2) || squareCoordinates == sf::Vector2i(7,5))
		return std::make_unique<Bishop>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	if (squareCoordinates == sf::Vector2i(0,3))
		return std::make_unique<Queen>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	if (squareCoordinates == sf::Vector2i(7,3))
		return std::make_unique<Queen>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	if (squareCoordinates == sf::Vector2i(0,4))
		return std::make_unique<King>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	if (squareCoordinates == sf::Vector2i(7,4))
		return std::make_unique<King>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	return nullptr;
}

void Board::createEvenRows(const sf::RenderWindow& window)
{
	//Build white-black rows
	for (int i = 0; i < boardSize; i += 2)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			sf::Vector2f squarePosition =
				std::move(sf::Vector2f(window.getSize().x / 4 + j * squareSize, window.getSize().y / 4 + i * squareSize));

			sf::Vector2i squareCoordinates = sf::Vector2i(i,j);

			if (j % 2 == 0)
				//Build a white square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize)
					.color(sf::Color(Colors::getInstance().getColor(Colors::ColorNames::LIGHT_BROWN)))
					.position(squarePosition)
					.build());
			else
				//Build a black square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize)
					.color(sf::Color(Colors::getInstance().getColor(Colors::ColorNames::DARK_BROWN)))
					.position(squarePosition)
					.build());
		}
	}
}

void Board::createOddRows(const sf::RenderWindow& window)
{
	//Build black-white rows
	for (int i = 1; i < boardSize; i += 2)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			sf::Vector2f squarePosition = 
				std::move(sf::Vector2f(window.getSize().x / 4 + j * squareSize, window.getSize().y / 4 + i * squareSize));

			sf::Vector2i squareCoordinates = sf::Vector2i(i, j);

			if (j % 2 == 0)
				//Build a black square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize)
					.color(Colors::getInstance().getColor(Colors::ColorNames::DARK_BROWN))
					.position(squarePosition)
					.build());
			else
				//Build a white square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize)
					.color(Colors::getInstance().getColor(Colors::ColorNames::LIGHT_BROWN))
					.position(squarePosition)
					.build());
		}
	}
}


Board::~Board()
{
}
