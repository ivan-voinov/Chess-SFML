#include "pch.h"
#include "Board.h"
#include "Piece.h"
#include "PieceHeaders.h"
#include "GameManager.h"


Board::Board()
{
}

const double Board::getSquareSize()
{
	return m_SquareSize;
}

bool Board::chooseSquareForPiece(const sf::Vector2i& mousePosition)
{
	std::vector<Square*> board = GameManager::getInstance().getGameObjects<Square>(m_SquareIds);
	for (auto& square : board)
	{
		if (square->isTriggered(mousePosition))
		{
			//Square has been chosen
			m_FocusedSquareId = square->getId();
			return true;
		}
	}
	//Square has not been chosen
	return false;
}

Square* Board::getFocusedSquare()
{
	return GameManager::getInstance().getGameObject<Square>(m_FocusedSquareId);
}

void Board::resetFocusedSquare()
{
	m_FocusedSquareId = -1;
}

bool Board::squareIsChosen() const
{
	return m_FocusedSquareId == -1 ? false : true;
}

//Build the pieces and assign them to players
void Board::assignPiecesToPlayers(Player& whitePlayer, Player& blackPlayer)
{
	std::vector<Square*> board = GameManager::getInstance().getGameObjects<Square>(m_SquareIds);
	for (const auto& square : board)
	{
		//Build the piece
		std::unique_ptr<Piece> piece = 
			getStartingSquarePiece(square->getCoordinates(), square->getPosition());

		//If built successfully, give it a reference to it's square and assign to a player
		if (piece != nullptr)
		{
			piece.get()->setSquare(*square);

			//If the piece is white, assign it to white player
			if (piece.get()->getColor() == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
			{
				whitePlayer.addPiece(piece->getId());
			}
			//If the piece is black, assign it to black player
			else if (piece.get()->getColor() == Colors::getInstance().getColor(Colors::ColorNames::BLACK))
			{
				blackPlayer.addPiece(piece->getId());
			}
			GameManager::getInstance().addGameObject(std::move(piece));
		}
	}
}

//Return the correct piece for the square at the start of the game
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

void Board::buildBoard(const sf::RenderWindow& window)
{
	//Build white-black rows
	for (int i = 0; i < m_BoardSize; ++i)
	{
		for (int j = 0; j < m_BoardSize; ++j)
		{
			sf::Vector2f squarePosition =
				std::move(sf::Vector2f(window.getSize().x / 4 + j * m_SquareSize, window.getSize().y / 4 + i * m_SquareSize));
			sf::Vector2i squareCoordinates = sf::Vector2i(i,j);

			if (i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0)
			{
				//Build a white square
				GameManager::getInstance().addGameObject(std::move(std::make_unique<Square>(SquareBuilder(squareCoordinates, m_SquareSize)
					.color(Colors::getInstance().getColor(Colors::ColorNames::LIGHT_BROWN))
					.position(squarePosition)
					.build())));
			}
			else
			{
				//Build a black square
				GameManager::getInstance().addGameObject(std::move(std::make_unique<Square>(SquareBuilder(squareCoordinates, m_SquareSize)
					.color(Colors::getInstance().getColor(Colors::ColorNames::DARK_BROWN))
					.position(squarePosition)
					.build())));
			}
		}
	}
}

Board::~Board()
{
}
