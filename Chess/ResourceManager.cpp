#include "pch.h"
#include "ResourceManager.h"

template class ResourceManager<sf::Texture>;
template class ResourceManager<sf::SoundBuffer>;

template<>
const sf::Texture* ResourceManager<sf::Texture>::loadResource(const std::string& resourcePath, const std::string& resourceKey)
{
	sf::Texture* pResource = &m_Resources[resourceKey];
	try
	{
		if (!pResource->loadFromFile(resourcePath))
			throw FileException("Error loading the texture from file: " + resourcePath);
		else
			return pResource;
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
		return nullptr;
	}
}

template<>
const sf::SoundBuffer* ResourceManager<sf::SoundBuffer>::loadResource(const std::string& resourcePath, const std::string& resourceKey)
{
	sf::SoundBuffer* pResource = &m_Resources[resourceKey];
	try
	{
		if (!pResource->loadFromFile(resourcePath))
			throw FileException("Error loading the SoundBuffer from file: " + resourcePath);
		else
			return pResource;
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
		return nullptr;
	}
}

template<>
const sf::Font* ResourceManager<sf::Font>::loadResource(const std::string& resourcePath, const std::string& resourceKey)
{
	sf::Font* pResource = &m_Resources[resourceKey];
	try
	{
		if (!pResource->loadFromFile(resourcePath))
			throw FileException("Error loading the Font from file: " + resourcePath);
		else
			return pResource;
	}
	catch (FileException& fileException)
	{
		std::cout << fileException.what();
		return nullptr;
	}
}