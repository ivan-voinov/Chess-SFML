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
				if (m_FocusedSquare == nullptr)
				{
					m_FocusedSquare = &square;
				}
				else
				{
					resetFocusedSquare();
					m_FocusedSquare = &square;
				}
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

void Board::resizePieces()
{
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			Piece* piece = square.getPiece();
			if (piece != nullptr)
				piece->resize(squareSize);
		}
	}
}

void Board::loadBoard(const sf::RenderWindow& window)
{
	createOddRows(window);
	createEvenRows(window);
	resizePieces();
}

void Board::addGameObjects()
{
	//Add squares
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			GameManager::getInstance().addGameObject(&square);
		}
	}

	//Add pieces
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			if (square.getPiece() != nullptr)
				GameManager::getInstance().addGameObject(square.getPiece());
		}
	}
}

void Board::assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer)
{
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			Piece* piece = m_Board[i][j].getPiece();

			if (piece != nullptr)
			{
				if (piece->getColor() == sf::Color::White)
					whitePlayer.addPiece(&m_Board[i][j]);

				else if (piece->getColor() == sf::Color::Black)
					blackPlayer.addPiece(&m_Board[i][j]);
			}
		}
	}
}

std::unique_ptr<Piece> Board::getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
	const sf::Vector2f& squarePosition) const
{
	if (squareCoordinates.x == 1)
		return std::make_unique<Pawn>(squarePosition, squareCoordinates, Square::blackColor);

	if (squareCoordinates.x == 6)
		return std::make_unique<Pawn>(squarePosition, squareCoordinates, Square::whiteColor);

	if (squareCoordinates == sf::Vector2i(0,0) || squareCoordinates == sf::Vector2i(0,7))
		return std::make_unique<Rook>(squarePosition, squareCoordinates, Square::blackColor);

	if (squareCoordinates == sf::Vector2i(7,0) || squareCoordinates == sf::Vector2i(7,7))
		return std::make_unique<Rook>(squarePosition, squareCoordinates, Square::whiteColor);

	if (squareCoordinates == sf::Vector2i(0,1) || squareCoordinates == sf::Vector2i(0,6))
		return std::make_unique<Knight>(squarePosition, squareCoordinates, Square::blackColor);

	if (squareCoordinates == sf::Vector2i(7,1) || squareCoordinates == sf::Vector2i(7,6))
		return std::make_unique<Knight>(squarePosition, squareCoordinates, Square::whiteColor);

	if (squareCoordinates == sf::Vector2i(0,2) || squareCoordinates == sf::Vector2i(0,5))
		return std::make_unique<Bishop>(squarePosition, squareCoordinates, Square::blackColor);

	if (squareCoordinates == sf::Vector2i(7,2) || squareCoordinates == sf::Vector2i(7,5))
		return std::make_unique<Bishop>(squarePosition, squareCoordinates, Square::whiteColor);

	if (squareCoordinates == sf::Vector2i(0,3))
		return std::make_unique<Queen>(squarePosition, squareCoordinates, Square::blackColor);

	if (squareCoordinates == sf::Vector2i(7,3))
		return std::make_unique<Queen>(squarePosition, squareCoordinates, Square::whiteColor);

	if (squareCoordinates == sf::Vector2i(0,4))
		return std::make_unique<King>(squarePosition, squareCoordinates, Square::blackColor);

	if (squareCoordinates == sf::Vector2i(7,4))
		return std::make_unique<King>(squarePosition, squareCoordinates, Square::whiteColor);

	return nullptr;
}

void Board::removeGameObject(GameObject* gameObject)
{
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			Piece* piece = square.getPiece();
			
			if (square.getPiece() == gameObject)
				square.setPiece(nullptr);
		}
	}
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
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(sf::Color(Square::lightBrownColor))
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());
			else
				//Build a black square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(sf::Color(Square::darkBrownColor))
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
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
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(Square::darkBrownColor)
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());
			else
				//Build a white square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(Square::lightBrownColor)
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());
		}
	}
}


Board::~Board()
{
}
