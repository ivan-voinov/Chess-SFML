#pragma once
#include <map>
#include <string>

class FilePaths
{
public:
	enum class FileNames
	{
		WHITE_BISHOP,
		WHITE_KING,
		WHITE_KNIGHT,
		WHITE_PAWN,
		WHITE_QUEEN,
		WHITE_ROOK,

		BLACK_BISHOP,
		BLACK_KING,
		BLACK_KNIGHT,
		BLACK_PAWN,
		BLACK_QUEEN,
		BLACK_ROOK,

		CHECKMATE
	};

private:
	FilePaths();
	const std::map<FileNames, std::string> m_FilePaths;

public:
	static FilePaths& getInstance();
	const std::string& getFilePath(const FileNames& filePath) const;
	~FilePaths();
};

