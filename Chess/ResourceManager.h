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
	const T* loadResource(const std::string& resourcePath, const std::string& resourceKey);

public:
	ResourceManager()
	{
	}

	//Return the resource if it exists; If it doesn't exist, check if there's a path for the resource.
	//If there is one, add it and return it. Otherwise, return nullptr
	const T* getResource(const std::string& requestedResource)
	{
		typename std::unordered_map<std::string, T>::const_iterator resourceIterator = m_Resources.find(requestedResource);
		if (resourceIterator == m_Resources.end())
		{
			AssetPaths assetPaths;
			const std::string* resourcePath = assetPaths.getAssetPath(requestedResource);
			if (resourcePath)
				return loadResource(*resourcePath, requestedResource);
			else
				return nullptr;
		}
		else
			return &resourceIterator->second;
	}
};
template<>
const sf::SoundBuffer* ResourceManager<sf::SoundBuffer>::loadResource(const std::string& resourcePath, const std::string& resourceKey);
template<>
const sf::Texture* ResourceManager<sf::Texture>::loadResource(const std::string& resourcePath, const std::string& resourceKey);
template<>
const sf::Font* ResourceManager<sf::Font>::loadResource(const std::string& resourcePath, const std::string& resourceKey);