#include "pch.h"
#include "ResourceManager.h"

template class ResourceManager<sf::Texture>;
template class ResourceManager<sf::SoundBuffer>;

void loadResource(const std::string& resourcePath, const std::string& resourceKey)
{
}

template<>
void ResourceManager<sf::Texture>::loadResource(const std::string& resourcePath, const std::string& resourceKey)
{
	m_Resources.emplace(resourceKey, sf::Texture());
	try
	{
		if (!m_Resources[resourceKey].loadFromFile(resourcePath))
			throw FileException("Error loading the texture from file: " + resourcePath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
}

template<>
ResourceManager<sf::Texture>::ResourceManager()
{
	AssetPaths assetPaths;
	std::vector<std::string> pieceNames{ "Bishop", "King", "Knight", "Pawn", "Queen", "Rook" };
	std::vector<std::string> colors{ "white", "black" };
	for (const auto& pieceName : pieceNames)
	{
		for (const auto& color : colors)
		{
			const std::string* texturePath = assetPaths.getAssetPath(color + pieceName);
			if (texturePath)
				loadResource(*texturePath, color + pieceName);
		}
	}
}

template<>
void ResourceManager<sf::SoundBuffer>::loadResource(const std::string& resourcePath, const std::string& resourceKey)
{
	m_Resources.emplace(resourceKey, sf::SoundBuffer());
	try
	{
		if (!m_Resources[resourceKey].loadFromFile(resourcePath))
			throw FileException("Error loading the SoundBuffer from file: " + resourcePath);
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
	}
}

template<>
ResourceManager<sf::SoundBuffer>::ResourceManager()
{
	AssetPaths assetPaths;
	const std::string soundKey{"checkMate"};
	const std::string* soundPath = assetPaths.getAssetPath(soundKey);
	if (soundPath)
		loadResource(*soundPath, soundKey);
}