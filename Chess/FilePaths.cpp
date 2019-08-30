#include "pch.h"
#include "FilePaths.h"

static const std::string ASSETS_PATH = "Assets";
static const std::string PIECES_PATH = ASSETS_PATH + "/Pieces";

FilePaths::FilePaths() :
	m_FilePaths
{
	{FileNames::WHITE_BISHOP, PIECES_PATH + "/whiteBishop.png"},
	{FileNames::WHITE_KING, PIECES_PATH + "/whiteKing.png"},
	{FileNames::WHITE_KNIGHT, PIECES_PATH + "/whiteKnight.png"},
	{FileNames::WHITE_PAWN, PIECES_PATH + "/whitePawn.png"},
	{FileNames::WHITE_QUEEN, PIECES_PATH + "/whiteQueen.png"},
	{FileNames::WHITE_ROOK, PIECES_PATH + "/whiteRook.png"},

	{FileNames::BLACK_BISHOP, PIECES_PATH + "/blackBishop.png"},
	{FileNames::BLACK_KING, PIECES_PATH + "/blackKing.png"},
	{FileNames::BLACK_KNIGHT, PIECES_PATH + "/blackKnight.png"},
	{FileNames::BLACK_PAWN, PIECES_PATH + "/blackPawn.png"},
	{FileNames::BLACK_QUEEN, PIECES_PATH + "/blackQueen.png"},
	{FileNames::BLACK_ROOK, PIECES_PATH + "/blackRook.png"}
}

{
}

const std::string& FilePaths::getFilePath(const FileNames& filePath) const
{
	return m_FilePaths.at(filePath);
}

FilePaths& FilePaths::getInstance()
{
	static FilePaths filePaths;
	return filePaths;
}

FilePaths::~FilePaths()
{
}
