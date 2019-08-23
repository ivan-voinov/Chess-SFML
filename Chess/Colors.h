#pragma once
#include <SFML/Graphics.hpp>

class Colors
{
public:
	enum class ColorNames
	{
		WHITE,
		BLACK,
		GREEN,
		DARK_BROWN,
		LIGHT_BROWN
	};

private:
	Colors();
	const std::map<ColorNames, sf::Color> m_Colors;

public:
	static Colors& getInstance();
	const sf::Color& getColor(const ColorNames& colorName) const;
	~Colors();
};

