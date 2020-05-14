#include "pch.h"
#include "AssetPaths.h"
#include <string>
#include <stdexcept> 
#include <iostream>

static const std::string ASSETS_PATH = "Assets";
static const std::string SOUNDS_PATH = ASSETS_PATH + "/Sounds";
static const std::string PIECES_PATH = ASSETS_PATH + "/Pieces";
static const std::string BUTTONS_PATH = ASSETS_PATH + "/Buttons";
static const std::string FONTS_PATH = ASSETS_PATH + "/Fonts";

const std::unordered_map<std::string, std::string> AssetPaths::m_AssetPaths
{
	{"whiteBishop", PIECES_PATH + "/whiteBishop.png"},
	{"whiteKing", PIECES_PATH + "/whiteKing.png"},
	{"whiteKnight", PIECES_PATH + "/whiteKnight.png"},
	{"whitePawn", PIECES_PATH + "/whitePawn.png"},
	{"whiteQueen", PIECES_PATH + "/whiteQueen.png"},
	{"whiteRook", PIECES_PATH + "/whiteRook.png"},

	{"blackBishop", PIECES_PATH + "/blackBishop.png"},
	{"blackKing", PIECES_PATH + "/blackKing.png"},
	{"blackKnight", PIECES_PATH + "/blackKnight.png"},
	{"blackPawn", PIECES_PATH + "/blackPawn.png"},
	{"blackQueen", PIECES_PATH + "/blackQueen.png"},
	{"blackRook", PIECES_PATH + "/blackRook.png"},
	{"checkMate", SOUNDS_PATH + "/checkmate.wav"},
	{"restartButton", BUTTONS_PATH + "/restartButton.png"},
	{"buttonFont", FONTS_PATH + "/buttonFont.otf"}
};

const std::string* AssetPaths::getAssetPath(const std::string& requestedAsset) const
{
	try
	{
		return &m_AssetPaths.at(requestedAsset);
	}
	catch (std::out_of_range e)
	{
		std::cout << "Error: the asset " + requestedAsset + " has not been found";
	}
	return nullptr;
}

AssetPaths::~AssetPaths()
{
}
