#include "pch.h"
#include "Board.h"
#include "Piece.h"
#include "PieceHeaders.h"
#include <iostream>
#include "ChessGame.h"


Board::Board()
{
}

bool Board::pieceIsChosen() const
{
	if (m_FocusedSquare == nullptr)
		return false;
	return true;
}

void Board::choosePiece(const sf::Vector2i& mousePosition)
{
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			if (square.isTriggered(mousePosition) && square.getPiece() != nullptr)
			{
				m_FocusedSquare = &square;
			}
		}
	}
}

void Board::chooseSquareForPiece(const sf::Vector2i& mousePosition)
{
	for (auto& rows : m_Board)
	{
		for (auto& square : rows)
		{
			if (square.isTriggered(mousePosition))
			{
				if (&square != m_FocusedSquare)
				{
					if (m_FocusedSquare->getPiece()->isLegalMove(square))
					{
						m_FocusedSquare->movePiece(square);
						m_FocusedSquare = nullptr;
					}
				}
				else
					m_FocusedSquare = nullptr;
			}
		}
	}
}

void Board::readInput(const sf::Vector2i& mousePosition)
{
	if (pieceIsChosen())
	{
		chooseSquareForPiece(mousePosition);
	}
	else
		choosePiece(mousePosition);
}

void Board::loadBoard(const sf::RenderWindow& window)
{
	createOddRows(window);
	createEvenRows(window);
}

std::unique_ptr<Piece> Board::getStartingSquarePiece(const sf::Vector2i& squareCoordinates,
	const sf::Vector2f& squarePosition) const
{
	if (squareCoordinates.x == 1)
		return std::make_unique<Pawn>(squarePosition, squareCoordinates, sf::Color::Black);

	if (squareCoordinates.x == 6)
		return std::make_unique<Pawn>(squarePosition, squareCoordinates, sf::Color::White);

	if (squareCoordinates == sf::Vector2i(0,0) || squareCoordinates == sf::Vector2i(0,7))
		return std::make_unique<Rook>(squarePosition, squareCoordinates, sf::Color::Black);

	if (squareCoordinates == sf::Vector2i(7,0) || squareCoordinates == sf::Vector2i(7,7))
		return std::make_unique<Rook>(squarePosition, squareCoordinates, sf::Color::White);

	if (squareCoordinates == sf::Vector2i(0,1) || squareCoordinates == sf::Vector2i(0,6))
		return std::make_unique<Knight>(squarePosition, squareCoordinates, sf::Color::Black);

	if (squareCoordinates == sf::Vector2i(7,1) || squareCoordinates == sf::Vector2i(7,6))
		return std::make_unique<Knight>(squarePosition, squareCoordinates, sf::Color::White);

	if (squareCoordinates == sf::Vector2i(0,2) || squareCoordinates == sf::Vector2i(0,5))
		return std::make_unique<Bishop>(squarePosition, squareCoordinates, sf::Color::Black);

	if (squareCoordinates == sf::Vector2i(7,2) || squareCoordinates == sf::Vector2i(7,5))
		return std::make_unique<Bishop>(squarePosition, squareCoordinates, sf::Color::White);

	if (squareCoordinates == sf::Vector2i(0,3))
		return std::make_unique<Queen>(squarePosition, squareCoordinates, sf::Color::Black);

	if (squareCoordinates == sf::Vector2i(7,3))
		return std::make_unique<Queen>(squarePosition, squareCoordinates, sf::Color::White);

	if (squareCoordinates == sf::Vector2i(0,4))
		return std::make_unique<King>(squarePosition, squareCoordinates, sf::Color::Black);

	if (squareCoordinates == sf::Vector2i(7,4))
		return std::make_unique<King>(squarePosition, squareCoordinates, sf::Color::White);

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
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(sf::Color(255, 229, 204))
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());
			else
				//Build a black square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(sf::Color(212,135,97))
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());

			ChessGame::getInstance().addDrawableObject(&m_Board[i][j]);
			if (m_Board[i][j].getPiece() != nullptr)
				ChessGame::getInstance().addDrawableObject(m_Board[i][j].getPiece());
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
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(sf::Color(212, 135, 97))
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());
			else
				//Build a white square
				m_Board[i][j] = std::move(SquareBuilder(squareCoordinates, squareSize).color(sf::Color(255, 229, 204))
					.position(squarePosition)
					.piece(getStartingSquarePiece(squareCoordinates, squarePosition))
					.build());

			ChessGame::getInstance().addDrawableObject(&m_Board[i][j]);
			if (m_Board[i][j].getPiece() != nullptr)
				ChessGame::getInstance().addDrawableObject(m_Board[i][j].getPiece());
		}
	}
}


Board::~Board()
{
}
