#include "pch.h"
#include "Player.h"
#include "Square.h"
#include "Colors.h"
#include "PieceHeaders.h"
#include "GameManager.h"
#include "Board.h"

#define MAX_X 8
#define MAX_Y 8
#define MAX_OPACITY 255
#define HALF_OPACITY 127


Player::Player(const sf::Color& playerColor)
{
	m_Color = playerColor;
	m_IsPlayerTurn = Colors::isWhite(m_Color);
}

void Player::attachSquareGetter(Board* squareGetter)
{
	m_Board = squareGetter;
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
				squareHolder = m_Board->getSquare(std::move(sf::Vector2i(i, j)));
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
	m_Board->setOpacity(HALF_OPACITY);
	setOpacity(HALF_OPACITY);
	m_Opponent->setOpacity(HALF_OPACITY);
}

void Player::onPawnPromotionCompleted(Piece& promotedPiece)
{
	const int queenIndex = 0;
	addPiece(promotedPiece.getId());
	m_MoveIsPaused = false;
	m_Board->setOpacity(MAX_OPACITY);
	setOpacity(MAX_OPACITY);
	m_Opponent->setOpacity(MAX_OPACITY);
	std::vector<Piece*> promotionPieces = GameManager::getInstance().getGameObjects<Piece>(m_PawnPromotionPiecesIds);
	promotedPiece.setSquare(*promotionPieces.at(queenIndex)->getSquare());
	promotedPiece.attachMoveValidator(this);
	promotedPiece.attachLineValidator(m_Board);
	promotedPiece.resize(m_Board->getSquareSize());
	for (const auto& piece : promotionPieces)
	{
		if (*piece != promotedPiece)
			piece->destroy();
	}
	m_PawnPromotionPiecesIds.clear();
	updateCheckedState();
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
			squaresForDisplayedPieces.push_back(*m_Board->getSquare(std::move(sf::Vector2i(i, currentCoords.y))));
	}
	else
	{
		for (int i = currentCoords.x; i < 4; i++)
			squaresForDisplayedPieces.push_back(*m_Board->getSquare(std::move(sf::Vector2i(i, currentCoords.y))));
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
	resetMoveState();

	if (pieceCaptured)
	{
		m_Opponent->removePiece(pieceCaptured->getId());
		pieceCaptured->destroy();
	}
	focusedPiece.move(square, false);
	//If the pawn is being promoted, don't complete the turn
	if (!m_MoveIsPaused)
		onSuccessfulMove(&focusedPiece);
}

void Player::onSuccessfulMove(Piece* piece)
{
	Pawn* lastMovedPawn = GameManager::getInstance().getGameObject<Pawn>(m_LastMovedPieceId);
	if (lastMovedPawn && lastMovedPawn->enPassantIsActive())
		lastMovedPawn->deactivateEnPassant();
	piece->onSuccessfulMove();
	m_LastMovedPieceId = piece->getId();
	updateCheckedState();
	m_Opponent->computeLegalMoves();
	switchTurn();
}

void Player::onFailedMove(Square& square)
{
	resetMoveState();
}

bool Player::processTurn(sf::RenderWindow& window)
{
	Piece* triggeredPiece = getTriggeredPiece(sf::Mouse::getPosition(window));
	Square* triggeredSquare = m_Board->getTriggeredSquare(sf::Mouse::getPosition(window));
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
	Square* focusedSquare = triggeredPiece.getSquare();
	m_FocusedSquareId = focusedSquare->getId();
	m_FocusedPieceId = triggeredPiece.getId();
	highlightSquare(*focusedSquare);
	triggeredPiece.displayLegalMoves();
}

void Player::switchTurn()
{
	m_IsPlayerTurn = !m_IsPlayerTurn;
	m_Opponent->m_IsPlayerTurn = !m_Opponent->isPlayerTurn();
}

void Player::resetMoveState()
{
	GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId)->hideLegalMoves();
	Square* focusedSquare = GameManager::getInstance().getGameObject<Square>(m_FocusedSquareId);
	focusedSquare->resetColor();
	m_FocusedPieceId = -1;
	m_FocusedSquareId = -1;
}

void Player::highlightSquare(Square& square)
{
	square.setColor(Colors::getColor(Colors::Names::GREEN));
}

void Player::updateCheckedState()
{
	King* enemyKing = m_Opponent->getKing();
	if (m_Opponent->isChecked())
	{
		Square* enemyKingSquare = enemyKing->getSquare();
		enemyKingSquare->setDisplayCheck(true);
		m_Opponent->m_CheckSquareId = enemyKingSquare->getId();
	}
	
	if (m_CheckSquareId != -1)
	{
		Square* checkSquare = GameManager::getInstance().getGameObject<Square>(m_CheckSquareId);
		checkSquare->setDisplayCheck(false);
	}
}

const sf::Color& Player::getColor() const
{
	return m_Color;
}

void Player::attachMoveValidatorToPieces()
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
		piece->attachMoveValidator(this);
}

void Player::setOpacity(sf::Uint8 opacity) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
		piece->setOpacity(opacity);
}

Rook* Player::getCastleRook(const Square& square, const Piece& piece) const
{
	sf::Vector2i rookCoords;
	if (square.getCoordinates().y == 6)
		rookCoords.y = 7;

	if (square.getCoordinates().y == 2)
		rookCoords.y = 0;

	if (Colors::isWhite(piece.getColor()))
		rookCoords.x = 7;
	else
		rookCoords.x = 0;

	return dynamic_cast<Rook*>(findPiece(*m_Board->getSquare(rookCoords)));
}

Square* Player::getCastleAttackedSquare(const Square& square, const Piece& piece) const
{
	sf::Vector2i attackedSquareCoords;

	if (square.getCoordinates().y == 6)
		attackedSquareCoords.y = 5;

	if (square.getCoordinates().y == 2)
		attackedSquareCoords.y = 3;

	if (Colors::isWhite(piece.getColor()))
		attackedSquareCoords.x = 7;
	else
		attackedSquareCoords.x = 0;

	return m_Board->getSquare(attackedSquareCoords);
}

Pawn* Player::getCapturedEnPassantPawn(const Square& square, const Piece& piece) const
{
	const sf::Vector2i& targetCoords = square.getCoordinates();
	const sf::Vector2i capturedPawnCoords = Colors::isWhite(piece.getColor()) ?
		sf::Vector2i(targetCoords.x + 1, targetCoords.y) : sf::Vector2i(targetCoords.x - 1, targetCoords.y);
	return dynamic_cast<Pawn*>(m_Opponent->findPiece(*m_Board->getSquare(capturedPawnCoords)));
}

bool Player::isLegalMove(Square& square, Piece& piece)
{
	bool isLegalMove = false;
	Piece* pieceCaptured = m_Opponent->findPiece(square);
	Square& startSquare = *piece.getSquare();

	if (pieceCaptured)
		m_Opponent->removePiece(pieceCaptured->getId());

	piece.move(square, true);

	if (!isChecked())
		isLegalMove = true;
	else
		isLegalMove = false;

	if (pieceCaptured)
		m_Opponent->addPiece(pieceCaptured->getId());
	piece.move(startSquare, true);
	return isLegalMove;
}

bool Player::castleIsLegal(Square& square, Piece& piece)
{
	bool castleIsLegal = false;
	Rook* castleRook = getCastleRook(square, piece);
	Square* attackedSquare = getCastleAttackedSquare(square, piece);

	if (castleRook &&
		castleRook->hasCastle() &&
		!m_Opponent->controlsSquare(*attackedSquare) &&
		!isChecked())
	{
		Square* startSquare = castleRook->getSquare();
		castleRook->move(*attackedSquare, true);
		castleIsLegal = isLegalMove(square, piece);
		castleRook->move(*startSquare, true);
	}
	return castleIsLegal;
}

bool Player::enPassantIsLegal(Square& square, Piece& piece)
{
	bool enPassantIsLegal = false;
	Pawn* pawn = getCapturedEnPassantPawn(square, piece);

	if (pawn && pawn->enPassantIsActive())
	{
		m_Opponent->removePiece(pawn->getId());
		enPassantIsLegal = isLegalMove(square, piece);
		m_Opponent->addPiece(pawn->getId());
	}
	return enPassantIsLegal;
}

void Player::castle(Square& square, Piece& piece) const
{
	Rook* castleRook = getCastleRook(square, piece);
	Square* attackedSquare = getCastleAttackedSquare(square, piece);
	castleRook->move(*attackedSquare, false);
}

void Player::enPassant(Square& square, Piece& piece) const
{
	Pawn* pawn = getCapturedEnPassantPawn(square, piece);
	pawn->getSquare()->setState(Square::State::IS_FREE);
	m_Opponent->removePiece(pawn->getId());
	pawn->destroy();
}

Player::~Player()
{
}