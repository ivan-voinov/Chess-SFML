#include "pch.h"
#include "Player.h"
#include "Square.h"
#include "Colors.h"
#include "PieceHeaders.h"
#include "GameManager.h"
#include "ISquareGetter.h"

#define MAX_X 8
#define MAX_Y 8
#define MAX_OPACITY 255
#define HALF_OPACITY 127


Player::Player(const sf::Color& playerColor)
{
	m_Color = playerColor;
	m_IsPlayerTurn = Colors::isWhite(m_Color);
}

void Player::attachSquareGetter(ISquareGetter* squareGetter)
{
	m_SquareGetter = squareGetter;
}

void Player::computeLegalMoves()
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Square* squareHolder = nullptr;
	for (const auto& piece : pieces)
	{
		piece->clearLegalSquares();
		for (int i = 0; i < MAX_X; i++)
			for (int j = 0; j < MAX_Y; j++)
			{
				squareHolder = m_SquareGetter->getSquare(std::move(sf::Vector2i(i, j)));
				if (piece->isLegalMove(*squareHolder))
					piece->addLegalSquare(squareHolder->getId());
			}
	}
}

void Player::onPawnPromotionTriggered(Square& square, Piece& piece)
{
	displayPiecesToChoose(getSquaresForDisplayedPieces(square));
	removePiece(piece.getId());
	piece.destroy();
	m_MoveIsPaused = true;
	//board.setOpacity(HALF_OPACITY);
	setOpacity(HALF_OPACITY);
}

void Player::onPawnPromotionCompleted(Piece& promotedPiece)
{
	const int queenIndex = 0;
	addPiece(promotedPiece.getId());
	m_MoveIsPaused = false;
	//board.setOpacity(MAX_OPACITY);
	setOpacity(MAX_OPACITY);
	std::vector<Piece*> promotionPieces = GameManager::getInstance().getGameObjects<Piece>(m_PawnPromotionPiecesIds);
	promotedPiece.setSquare(*promotionPieces.at(queenIndex)->getSquare());
	for (const auto& piece : promotionPieces)
	{
		if (*piece != promotedPiece)
			piece->destroy();
	}
	m_PawnPromotionPiecesIds.clear();
	//TODO: update checked state
	m_Opponent->computeLegalMoves();
	switchTurn();
}

std::vector<std::reference_wrapper<Square>> Player::getSquaresForDisplayedPieces(Square& square) const
{
	const sf::Vector2i& currentCoords = square.getCoordinates();
	std::vector<std::reference_wrapper<Square>> squaresForDisplayedPieces;
	if (currentCoords.x == 7)
	{
		for (int i = currentCoords.x; i > 3; i--)
			squaresForDisplayedPieces.push_back(*m_SquareGetter->getSquare(std::move(sf::Vector2i(i, currentCoords.y))));
	}
	else
	{
		for (int i = currentCoords.x; i < 4; i++)
			squaresForDisplayedPieces.push_back(*m_SquareGetter->getSquare(std::move(sf::Vector2i(i, currentCoords.y))));
	}
	return squaresForDisplayedPieces;
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
				break;
			case 1:
				piece = std::make_unique<Knight>(square.get().getPosition(), square.get().getId(), m_Color);
				break;
			case 2:
				piece = std::make_unique<Rook>(square.get().getPosition(), square.get().getId(), m_Color);
				break;
			case 3:
				piece = std::make_unique<Bishop>(square.get().getPosition(), square.get().getId(), m_Color);
				break;
		}
		m_PawnPromotionPiecesIds.push_back(piece->getId());
		GameManager::getInstance().addGameObject(std::move(piece));
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
	for (const auto& piece : pieces)
	{
		if (piece->isTriggered(mousePosition))
			return piece;
	}
	return nullptr;
}

Piece* Player::getTriggeredPromotedPiece(const sf::Vector2i& mousePosition) const
{
	std::vector<Piece*> promotionPieces = GameManager::getInstance().getGameObjects<Piece>(m_PawnPromotionPiecesIds);
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

bool Player::isChecked() const
{
	King* king = getKing();
	return m_Opponent->controlsSquare(*king->getSquare());
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

bool Player::controlsSquare(Square& square)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
	{
		if (piece->controlsSquare(square))
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

void Player::makeMove(Square& square, Piece& focusedPiece)
{
	Piece* pieceCaptured = m_Opponent->findPiece(square);
	Square& startSquare = *focusedPiece.getSquare();
	resetMoveState(startSquare);

	if (pieceCaptured)
	{
		m_Opponent->removePiece(pieceCaptured->getId());
		pieceCaptured->destroy();
	}
	focusedPiece.move(square, false);
	//If the pawn is being promoted, don't complete the turn
	if (!m_MoveIsPaused)
		onSuccessfulMove(startSquare , &focusedPiece);
}

void Player::onSuccessfulMove(Square& startSquare, Piece* piece)
{
	Pawn* lastMovedPawn = GameManager::getInstance().getGameObject<Pawn>(m_LastMovedPieceId);
	if (lastMovedPawn && lastMovedPawn->enPassantIsActive())
		lastMovedPawn->deactivateEnPassant();
	piece->onSuccessfulMove();
	m_LastMovedPieceId = piece->getId();
	updateCheckedState(startSquare, *piece);
	m_Opponent->computeLegalMoves();
	switchTurn();
}

void Player::onFailedMove(Square& square)
{
	resetMoveState(square);
}

bool Player::processTurn(sf::RenderWindow& window)
{
	Piece* triggeredPiece = getTriggeredPiece(sf::Mouse::getPosition(window));
	Square* triggeredSquare = m_SquareGetter->getTriggeredSquare(sf::Mouse::getPosition(window));
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);

	if (!m_MoveIsPaused)
	{
		if (!pieceIsChosen())
		{
			if (triggeredPiece)
			{
				choosePiece(*triggeredPiece);
			}
		}
		else
		{
			if (triggeredSquare && focusedPiece->findLegalSquare(*triggeredSquare))
			{
				makeMove(*triggeredSquare, *focusedPiece);
				//If the pawn was promoted, return false because the move has not been completed
				if (!m_MoveIsPaused)
					return true;
				return false;
			}
			else
				onFailedMove(*focusedPiece->getSquare());
		}
	}
	else
	{
		Piece* piece = getTriggeredPromotedPiece(sf::Mouse::getPosition(window));
		if (piece)
		{
			onPawnPromotionCompleted(*piece);
			return true;
		}
	}
	return false;
}

void Player::choosePiece(Piece& triggeredPiece)
{
	m_FocusedPieceId = triggeredPiece.getId();
	highlightSquare(*triggeredPiece.getSquare());
	triggeredPiece.displayLegalMoves();
}

void Player::switchTurn()
{
	m_IsPlayerTurn = !m_IsPlayerTurn;
	m_Opponent->m_IsPlayerTurn = !m_Opponent->isPlayerTurn();
}

void Player::resetMoveState(Square& square)
{
	GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId)->hideLegalMoves();
	m_FocusedPieceId = -1;
	square.resetColor();
}

void Player::highlightSquare(Square& square)
{
	square.setColor(Colors::getColor(Colors::Names::GREEN));
}

void Player::updateCheckedState(Square& startSquare, Piece& piece) const
{
	King* enemyKing = m_Opponent->getKing();
	King* king = getKing();
	if (m_Opponent->isChecked())
		enemyKing->getSquare()->setDisplayCheck(true);
	if (*king == piece)
		startSquare.setDisplayCheck(false);
	else
		king->getSquare()->setDisplayCheck(false);
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

void Player::setOpacity(sf::Uint8 opacity) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
		piece->setOpacity(opacity);
}

Player::~Player()
{
}