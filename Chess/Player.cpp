#include "pch.h"
#include "Player.h"
#include "Square.h"
#include <vector>
#include "Piece.h"
#include "King.h"
#include "PieceHeaders.h"
#include "Board.h"
#include "GameManager.h"

#define MAX_X 8
#define MAX_Y 8
#define MAX_OPACITY 255
#define HALF_OPACITY 127



Player::Player(const sf::Color& playerColor)
{
	m_Color = playerColor;

	if (Colors::isWhite(m_Color))
	{
		m_IsPlayerTurn = true;
	}
	else
		m_IsPlayerTurn = false;
}

void Player::computeLegalMoves(const Board& board)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Square* squareHolder = nullptr;
	for (const auto& piece : pieces)
	{
		piece->clearLegalSquares();
		for (int i = 0; i < MAX_X; i++)
			for (int j = 0; j < MAX_Y; j++)
			{
				squareHolder = board.getSquare(std::move(sf::Vector2i(i, j)));
				if (piece->isLegalMove(*squareHolder, board))
					piece->addLegalSquare(squareHolder->getId());
			}
	}
}

void Player::onPawnPromotionTriggered(Square& square, Board& board)
{
	displayPiecesToChoose(getSquaresForDisplayedPieces(square, board));
	m_MoveIsPaused = true;
	board.setOpacity(HALF_OPACITY);
}

void Player::onPawnPromotionCompleted(Board& board)
{
	m_MoveIsPaused = false;
	board.setOpacity(MAX_OPACITY);
	std::vector<Piece*> promotionPieces = GameManager::getInstance().getGameObjects<Piece>(m_PawnPromotionPieces);
	for (const auto& piece : promotionPieces)
	{
		piece->destroy();
	}
	m_PawnPromotionPieces.clear();
}

std::vector<std::reference_wrapper<Square>> Player::getSquaresForDisplayedPieces(Square& square, const Board& board) const
{
	sf::Vector2i currentCoords = square.getCoordinates();
	std::vector<std::reference_wrapper<Square>> squaresForDisplayedPieces;
	if (currentCoords.x == 7)
	{
		for (int i = currentCoords.x; i > 3; i--)
			squaresForDisplayedPieces.push_back(*board.getSquare(std::move(sf::Vector2i(i, currentCoords.y))));
	}
	else
	{
		for (int i = currentCoords.x; i < 4; i++)
			squaresForDisplayedPieces.push_back(*board.getSquare(std::move(sf::Vector2i(i, currentCoords.y))));
	}
	return std::move(squaresForDisplayedPieces);
}

void Player::displayPiecesToChoose(const std::vector<std::reference_wrapper<Square>>& squaresForDisplayedPieces)
{
	int i = 0;
	for (const auto& square : squaresForDisplayedPieces)
	{
		std::unique_ptr<Piece> piece;
		switch (i)
		{
			case 0:
				piece = std::make_unique<Queen>(square.get().getPosition(), square.get().getId(), m_Color);
				m_PawnPromotionPieces.push_back(piece->getId());
				GameManager::getInstance().addGameObject(std::move(piece));
				break;
			case 1:
				piece = std::make_unique<Knight>(square.get().getPosition(), square.get().getId(), m_Color);
				m_PawnPromotionPieces.push_back(piece->getId());
				GameManager::getInstance().addGameObject(std::move(piece));
				break;
			case 2:
				piece = std::make_unique<Rook>(square.get().getPosition(), square.get().getId(), m_Color);
				m_PawnPromotionPieces.push_back(piece->getId());
				GameManager::getInstance().addGameObject(std::move(piece));
				break;
			case 3:
				piece = std::make_unique<Bishop>(square.get().getPosition(), square.get().getId(), m_Color);
				m_PawnPromotionPieces.push_back(piece->getId());
				GameManager::getInstance().addGameObject(std::move(piece));
				break;
		}
		i++;
	}
}

void Player::addPiece(int pieceId)
{
	m_PiecesIds.push_back(pieceId);
}

Piece* Player::getTriggeredPiece(const sf::Vector2i& mousePosition) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	for (const auto& piece : pieces)
	{
		if (piece->isTriggered(mousePosition))
			return piece;
	}
	return nullptr;
}

Piece* Player::getTriggeredPromotedPiece(const sf::Vector2i& mousePosition) const
{
	std::vector<Piece*> promotionPieces = GameManager::getInstance().getGameObjects<Piece>(m_PawnPromotionPieces);
	for (const auto& piece : promotionPieces)
	{
		if (piece->isTriggered(mousePosition))
			return piece;
	}
	return nullptr;
}

void Player::removePiece(int capturedPieceId)
{
	m_PiecesIds.erase(std::remove_if(
		m_PiecesIds.begin(),
		m_PiecesIds.end(),
		[&capturedPieceId](int gmObjId) {return gmObjId == capturedPieceId;}));
}

bool Player::isChecked(const Board& board) const
{
	King* king = getKing();
	return m_Opponent->controlsSquare(*king->getSquare(), board);
}

bool Player::hasNoLegalMoves() const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
		if (!piece->hasNoLegalSquares())
			return false;
	return true;
}

Piece* Player::findPiece(const Square& square) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (auto& piece : pieces)
	{
		if (piece->getSquare() == &square)
			return piece;
	}
	return nullptr;
}

King* Player::getKing() const
{
	return GameManager::getInstance().getGameObject<King>(m_KingId);
}

void Player::attachOpponent(Player& opponent)
{
	m_Opponent = &opponent;
}

void Player::setKing(int kingId)
{
	m_KingId = kingId;
}

bool Player::controlsSquare(Square& square, const Board& board)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
	{
		if (piece->controlsSquare(square, board))
			return true;
	}
	return false;
}

void Player::resizePieces(double squareSize)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (auto& piece : pieces)
		piece->resize(squareSize);
}

bool Player::pieceIsChosen() const
{
	return m_FocusedPieceId != -1;
}

bool Player::isPlayerTurn() const
{
	return m_IsPlayerTurn;
}

void Player::makeMove(Square& square, Board& board, Piece& focusedPiece)
{
	Piece* pieceCaptured = m_Opponent->findPiece(square);
	Square& startSquare = *focusedPiece.getSquare();

	if (pieceCaptured)
	{
		m_Opponent->removePiece(pieceCaptured->getId());
		pieceCaptured->destroy();
	}
	focusedPiece.move(square, false);
	onSuccessfulMove(board, startSquare, focusedPiece);
}

void Player::onSuccessfulMove(Board& board, Square& startSquare, Piece& piece)
{
	Pawn* lastMovedPawn = GameManager::getInstance().getGameObject<Pawn>(m_LastMovedPieceId);
	if (lastMovedPawn && lastMovedPawn->enPassantIsActive())
		lastMovedPawn->deactivateEnPassant();
	piece.onSuccessfulMove();
	resetMoveState(startSquare);
	m_LastMovedPieceId = piece.getId();
	King* enemyKing = m_Opponent->getKing();
	King* king = getKing();
	if (m_Opponent->isChecked(board))
		enemyKing->getSquare()->setDisplayCheck(true);
	if (*king == piece)
		startSquare.setDisplayCheck(false);
	else
		king->getSquare()->setDisplayCheck(false);
	m_Opponent->computeLegalMoves(board);
	switchTurn();
}

void Player::onFailedMove(Square& square)
{
	resetMoveState(square);
}

bool Player::processTurn(Board& board, sf::RenderWindow& window)
{
	Piece* triggeredPiece = getTriggeredPiece(sf::Mouse::getPosition(window));
	Square* triggeredSquare = board.getTriggeredSquare(sf::Mouse::getPosition(window));
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);

	if (!pieceIsChosen())
	{
		if (triggeredPiece)
		{
			choosePiece(board, *triggeredPiece);
		}
	}
	else
	{
		if (triggeredSquare && focusedPiece->findLegalSquare(*triggeredSquare))
		{
			makeMove(*triggeredSquare, board, *focusedPiece);
			return true;
		}
		else
			onFailedMove(*focusedPiece->getSquare());
	}
	return false;
}

void Player::choosePiece(const Board& board, Piece& triggeredPiece)
{
	m_FocusedPieceId = triggeredPiece.getId();
	highlightSquare(*triggeredPiece.getSquare());
	triggeredPiece.toggleLegalSquares();
}

void Player::switchTurn()
{
	m_IsPlayerTurn = !m_IsPlayerTurn;
	m_Opponent->m_IsPlayerTurn = !m_Opponent->isPlayerTurn();
}

void Player::resetMoveState(Square& square)
{
	GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId)->toggleLegalSquares();
	m_FocusedPieceId = -1;
	square.resetColor();
}

void Player::highlightSquare(Square& square)
{
	square.setColor(Colors::getColor(Colors::Names::GREEN));
}

const sf::Color& Player::getColor() const
{
	return m_Color;
}

void Player::setMoveValidator(MoveValidator& moveValidator)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
		piece->setMoveValidator(moveValidator);
}

Player::~Player()
{
}