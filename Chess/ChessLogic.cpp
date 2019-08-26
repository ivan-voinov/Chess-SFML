#include "pch.h"
#include "ChessLogic.h"
#include "GameManager.h"


ChessLogic::ChessLogic(Board* board, Player* whitePlayer, Player* blackPlayer)
{
	m_Board = board;
	m_WhitePlayer = whitePlayer;
	m_BlackPlayer = blackPlayer;
}

void ChessLogic::onClick(sf::RenderWindow& window)
{
	if (m_WhitePlayer->isPlayerTurn())
	{
		processPlayerTurn(*m_WhitePlayer, *m_BlackPlayer, window);
	}
	else
	{
		if (m_BlackPlayer->isPlayerTurn())
		{
			processPlayerTurn(*m_BlackPlayer, *m_WhitePlayer, window);
		}
	}
}

void ChessLogic::processPlayerTurn(Player& activePlayer, Player& inactivePlayer, sf::RenderWindow& window)
{
	if (activePlayer.pieceIsChosen())
	{
		m_Board->chooseSquareForPiece(sf::Mouse::getPosition(window));

		SquareState squareState = getSquareState(activePlayer, inactivePlayer, *m_Board->getFocusedSquare());

		switch (squareState)
		{
		case SquareState::IS_FREE:
		{
			if (activePlayer.isLegalMove(*m_Board->getFocusedSquare()))
			{
				activePlayer.resetFocusedPieceColor();
				activePlayer.makeMove(*m_Board->getFocusedSquare());
				activePlayer.resetFocusedPiece();
				activePlayer.endTurn();
				inactivePlayer.startTurn();
			}
			else
			{
				//Reset the color of the square with selected piece
				activePlayer.resetFocusedPieceColor();

				//Reset the focused piece
				activePlayer.resetFocusedPiece();
			}

			break;
		}

		case SquareState::HAS_FRIENDLY_PIECE:
		{
			//Reset the color of the square with selected piece
			activePlayer.resetFocusedPieceColor();

			//Reset the focused piece
			activePlayer.resetFocusedPiece();

			break;
		}

		case SquareState::HAS_ENEMY_PIECE:
		{
			if (activePlayer.isLegalMove(*m_Board->getFocusedSquare()))
			{
				activePlayer.resetFocusedPieceColor();
				GameManager::getInstance().removeGameObject(inactivePlayer.findPieceBySquare(*m_Board->getFocusedSquare()));
				activePlayer.makeMove(*m_Board->getFocusedSquare());
				activePlayer.resetFocusedPiece();
				activePlayer.endTurn();
				inactivePlayer.startTurn();
			}
			else
			{
				//Reset the color of the square with selected piece
				activePlayer.resetFocusedPieceColor();

				//Reset the focused piece
				activePlayer.resetFocusedPiece();
			}

			break;
		}

		case SquareState::IS_BLOCKED:
		{
			//Reset the color of the square with selected piece
			activePlayer.resetFocusedPieceColor();

			//Reset the focused piece
			activePlayer.resetFocusedPiece();

			break;
		}

		}
	}

	else
	{
		activePlayer.choosePiece(sf::Mouse::getPosition(window));
	}
}

ChessLogic::SquareState ChessLogic::getSquareState(const Player& activePlayer, 
	const Player& inactivePlayer, 
	const Square& square)
{
	if (activePlayer.findPieceBySquare(square) != nullptr)
		return SquareState::HAS_FRIENDLY_PIECE;

	else
		if (inactivePlayer.findPieceBySquare(square) != nullptr)
			return SquareState::HAS_ENEMY_PIECE;
		else
			//if ()
			//	//TO DO IS BLOCKED CASE
			//else
				return SquareState::IS_FREE;
			
}

ChessLogic::~ChessLogic()
{
}
