#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "ITriggered.h"
#include "GameObject.h"

class Button : public GameObject, public ITriggered
{
private:
	sf::Sprite m_Sprite;
	sf::Text m_Text;
	sf::Font m_Font;
	bool m_FocusState = false;
	std::function<void()> m_OnClickAction;

public:
	Button(const std::string& textureRoute, const std::string& fontRoute);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setOnClickAction(std::function<void()> clickAction);
	bool isTriggered(const sf::Vector2i& mousePosition) const override;
	void toggleFocus();
	bool getFocus();
	void glow();
	void increaseSize();
	void decreaseSize();
	void executeAction() const;
	void loadTextFont(const std::string& fontRoute);
	void loadTexture(const std::string& textureRoute);
	void setSize(const sf::Vector2f& scale);
	const sf::Vector2f getSize() const;
	void setText(const sf::Text& text);
	void setTextColor(const sf::Color& color);
	void setTextSize(int size);
	void setPosition(const sf::Vector2f& position);
	void setTextString(const std::string& textString);
	~Button();
};

