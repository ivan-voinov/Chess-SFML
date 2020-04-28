#include "pch.h"
#include "Colors.h"

const std::map<Colors::Names, sf::Color> Colors::m_Colors
{
	{Names::WHITE, sf::Color(255, 255, 255)},
	{Names::BLACK, sf::Color(0, 0, 0)},
	{Names::GREEN, sf::Color(11, 176, 5)},
	{Names::LIGHT_BROWN, sf::Color(255, 229, 204)},
	{Names::DARK_BROWN, sf::Color(212, 135, 97)},
	{Names::RED, sf::Color(255, 0, 0, 200)}
};

const sf::Color& Colors::getColor(const Names& colorName)
{
	return m_Colors.at(colorName);
}

const bool Colors::isWhite(const sf::Color& color)
{
	return color == m_Colors.at(Names::WHITE);
}

const bool Colors::isBlack(const sf::Color& color)
{
	return color == m_Colors.at(Names::BLACK);
}

Colors::~Colors()
{
}
