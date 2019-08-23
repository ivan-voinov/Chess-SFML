#include "pch.h"
#include "Colors.h"


Colors::Colors() : m_Colors
{
	{ColorNames::WHITE, sf::Color(sf::Color::White)},
	{ColorNames::BLACK, sf::Color(sf::Color::Black)},
	{ColorNames::GREEN, sf::Color(11, 176, 5)},
	{ColorNames::LIGHT_BROWN, sf::Color(255, 229, 204)},
	{ColorNames::DARK_BROWN, sf::Color(212, 135, 97)}
}

{
}

const sf::Color& Colors::getColor(const ColorNames& colorName) const
{
	return m_Colors.at(colorName);
}

Colors& Colors::getInstance()
{
	static Colors filePaths;
	return filePaths;
}

Colors::~Colors()
{
}
