#include "pch.h"
#include "Board.h"
#include "Piece.h"
#include "PieceHeaders.h"
#include "GameManager.h"


Board::Board()
{
}

const int Board::getSquareSize()
{
	return m_SquareSize;
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
	//Register the squares in game manager
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			GameManager::getInstance().addGameObject(&square);
		}
	}
}

//Builds the pieces and assigns them to players
void Board::assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer)
{
	for (int i = 0; i < m_BoardSize; ++i)
	{
		for (int j = 0; j < m_BoardSize; ++j)
		{
			//Build the piece
			std::unique_ptr<Piece> piece = 
				getStartingSquarePiece(m_Board[i][j].getCoordinates(), m_Board[i][j].getPosition());

			//If build successfully, give it a reference to it's square and assign to a player
			if (piece != nullptr)
			{
				piece.get()->setSquare(m_Board[i][j]);

				//If the piece is white, assign it to white player
				if (piece.get()->getColor() == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
				{
					whitePlayer.addPiece(std::move(piece));
				}
				//If the piece is black, assign it to black player
				else if (piece.get()->getColor() == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
				{
					blackPlayer.addPiece(std::move(piece));
				}
			}
		}
	}
}

//Returns the correct piece for the square at the start of the game
std::unique_ptr<Piece> Board::getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
	const sf::Vector2f& squarePosition) const
{
	//Return black pawn
	if (squareCoordinates.x == 1)
		return std::make_unique<Pawn>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	//Return white pawn
	if (squareCoordinates.x == 6)
		return std::make_unique<Pawn>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	//Return black rook
	if (squareCoordinates == sf::Vector2i(0,0) || squareCoordinates == sf::Vector2i(0,7))
		return std::make_unique<Rook>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	//Return white rook
	if (squareCoordinates == sf::Vector2i(7,0) || squareCoordinates == sf::Vector2i(7,7))
		return std::make_unique<Rook>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	//Return black knight
	if (squareCoordinates == sf::Vector2i(0,1) || squareCoordinates == sf::Vector2i(0,6))
		return std::make_unique<Knight>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	//Return white knight
	if (squareCoordinates == sf::Vector2i(7,1) || squareCoordinates == sf::Vector2i(7,6))
		return std::make_unique<Knight>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	//Return black bishop
	if (squareCoordinates == sf::Vector2i(0,2) || squareCoordinates == sf::Vector2i(0,5))
		return std::make_unique<Bishop>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	//Return white bishop
	if (squareCoordinates == sf::Vector2i(7,2) || squareCoordinates == sf::Vector2i(7,5))
		return std::make_unique<Bishop>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	//Return black queen
	if (squareCoordinates == sf::Vector2i(0,3))
		return std::make_unique<Queen>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	//Return white queen
	if (squareCoordinates == sf::Vector2i(7,3))
		return std::make_unique<Queen>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	//Return black king
	if (squareCoordinates == sf::Vector2i(0,4))
		return std::make_unique<King>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::BLACK));

	//Return white king
	if (squareCoordinates == sf::Vector2i(7,4))
		return std::make_unique<King>(squarePosition, Colors::getInstance().getColor(Colors::ColorNames::WHITE));

	return nullptr;
}

void Board::createEvenRows(const sf::RenderWindow& window)
{
	//Build white-black rows
	for (int i = 0; i < m_BoardSize; i += 2)
	{
		for (int j = 0; j < m_BoardSize; ++j)
		{
			sf::Vector2f squarePosition =
				std::move(sf::Vector2f(window.getSize().x / 4 + j * m_SquareSize, window.getSize().y / 4 + i * m_SquareSize));

			sf::Vector2i squareCoordinates = sf::Vector2i(i,j);

			if (j % 2 == 0)
				//Build a white square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, m_SquareSize)
					.color(sf::Color(Colors::getInstance().getColor(Colors::ColorNames::LIGHT_BROWN)))
					.position(squarePosition)
					.build());
			else
				//Build a black square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, m_SquareSize)
					.color(sf::Color(Colors::getInstance().getColor(Colors::ColorNames::DARK_BROWN)))
					.position(squarePosition)
					.build());
		}
	}
}

void Board::createOddRows(const sf::RenderWindow& window)
{
	//Build black-white rows
	for (int i = 1; i < m_BoardSize; i += 2)
	{
		for (int j = 0; j < m_BoardSize; ++j)
		{
			sf::Vector2f squarePosition = 
				std::move(sf::Vector2f(window.getSize().x / 4 + j * m_SquareSize, window.getSize().y / 4 + i * m_SquareSize));

			sf::Vector2i squareCoordinates = sf::Vector2i(i, j);

			if (j % 2 == 0)
				//Build a black square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, m_SquareSize)
					.color(Colors::getInstance().getColor(Colors::ColorNames::DARK_BROWN))
					.position(squarePosition)
					.build());
			else
				//Build a white square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, m_SquareSize)
					.color(Colors::getInstance().getColor(Colors::ColorNames::LIGHT_BROWN))
					.position(squarePosition)
					.build());
		}
	}
}


Board::~Board()
{
}
