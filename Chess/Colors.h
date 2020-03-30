#pragma once
#include <SFML/Graphics.hpp>

class Colors
{
public:
	enum class Names
	{
		WHITE,
		BLACK,
		GREEN,
		DARK_BROWN,
		LIGHT_BROWN
	};

private:
	static const std::map<Names, sf::Color> m_Colors;

public:
	static const sf::Color& getColor(const Names& colorName);
	~Colors();
};

