#include "pch.h"
#include "ChessLogic.h"


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
		if (m_WhitePlayer->pieceIsChosen())
		{
			m_Board->chooseSquareForPiece(sf::Mouse::getPosition(window));

			if (m_WhitePlayer->isLegalMove(*m_Board->getFocusedSquare()))
			{
				m_WhitePlayer->resetFocusedPieceColor();
				m_WhitePlayer->makeMove(*m_Board->getFocusedSquare());
				m_WhitePlayer->resetFocusedPiece();
				m_WhitePlayer->endTurn();
				m_BlackPlayer->startTurn();
			}
			else
			{
				//Reset the color of the square with selected piece
				m_WhitePlayer->resetFocusedPieceColor();

				//Reset the focused piece
				m_WhitePlayer->resetFocusedPiece();
			}
		}
		else
		{
			m_WhitePlayer->choosePiece(sf::Mouse::getPosition(window));
		}
	}
	else
	{
		if (m_BlackPlayer->isPlayerTurn())
		{
			if (m_BlackPlayer->pieceIsChosen())
			{
				m_Board->chooseSquareForPiece(sf::Mouse::getPosition(window));

				if (m_BlackPlayer->isLegalMove(*m_Board->getFocusedSquare()))
				{
					m_BlackPlayer->resetFocusedPieceColor();
					m_BlackPlayer->makeMove(*m_Board->getFocusedSquare());
					m_BlackPlayer->resetFocusedPiece();
					m_BlackPlayer->endTurn();
					m_WhitePlayer->startTurn();
				}
				else
				{
					//Reset the color of the square with selected piece
					m_BlackPlayer->resetFocusedPieceColor();

					//Reset the focused piece
					m_BlackPlayer->resetFocusedPiece();
				}
			}
			else
			{
				m_BlackPlayer->choosePiece(sf::Mouse::getPosition(window));
			}
		}
	}
}


ChessLogic::~ChessLogic()
{
}
