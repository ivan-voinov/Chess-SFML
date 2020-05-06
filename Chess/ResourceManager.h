#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "AssetPaths.h"
#include "FileException.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <stdexcept>

template<class T>
class ResourceManager
{
private:
	std::unordered_map<std::string, T> m_Resources;
	void loadResource(const std::string& resourcePath, const std::string& resourceKey);

public:
	ResourceManager()
	{
	}

	const T& getResource(const std::string& requestedResource) const
	{
		try
		{
			return m_Resources.at(requestedResource);
		}
		catch (std::out_of_range e)
		{
			std::cout << "Error: the resource " + requestedResource + " has not been found";
		}
	}
};

template<>
ResourceManager<sf::SoundBuffer>::ResourceManager();

template<>
void ResourceManager<sf::SoundBuffer>::loadResource(const std::string& resourcePath, const std::string& resourceKey);

template<>
ResourceManager<sf::Texture>::ResourceManager();

template<>
void ResourceManager<sf::Texture>::loadResource(const std::string& resourcePath, const std::string& resourceKey);