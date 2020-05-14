#include "pch.h"
#include "Button.h"
#include "ResourceManager.h"
#include "GameManager.h"

Button::Button(const std::string& textureRoute, const std::string& fontRoute)
{
	loadTexture(textureRoute);
	loadTextFont(fontRoute);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
	target.draw(m_Text);
}

void Button::setOnClickAction(std::function<void()> clickAction)
{
	m_OnClickAction = clickAction;
}

bool Button::isTriggered(const sf::Vector2i& mousePosition) const
{
	return m_Sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

void Button::toggleFocus(bool focus)
{
	m_PreviousFocusState = m_FocusState;
	m_FocusState = focus;
	if (m_PreviousFocusState != m_FocusState)
		onFocusChanged();
}

bool Button::isFocused()
{
	return m_FocusState;
}

void Button::glow()
{
	//not ready
}

void Button::increaseSize()
{
	m_Sprite.scale(1.1f, 1.1f);
}

void Button::decreaseSize()
{
	m_Sprite.scale(10.0f / 11.0f, 10.0f / 11.0f);
}

void Button::executeAction() const
{
	m_OnClickAction();
}

void Button::loadTextFont(const std::string& fontRoute)
{
	const sf::Font* textFont = GameManager::getInstance().getFontManager().getResource(fontRoute);
	if (textFont)
		m_Text.setFont(*textFont);
}

void Button::loadTexture(const std::string& textureRoute)
{
	const sf::Texture* buttonTexture = GameManager::getInstance().getTextureManager().getResource(textureRoute);
	if (buttonTexture)
		m_Sprite.setTexture(*buttonTexture);
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
}

void Button::setSize(const sf::Vector2f& size)
{
	m_Sprite.setScale(size.x / m_Sprite.getTextureRect().width, size.y / m_Sprite.getTextureRect().height);
	m_Text.setScale(size.x / m_Sprite.getTextureRect().width, size.y / m_Sprite.getTextureRect().height);
}

const sf::Vector2f Button::getSize() const
{
	return sf::Vector2f(m_Sprite.getLocalBounds().width, m_Sprite.getLocalBounds().height);
}

void Button::setText(const sf::Text& text)
{
	m_Text = text;
}

void Button::setTextColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

void Button::setTextSize(int size)
{
	m_Text.setCharacterSize(size);
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_Sprite.setPosition(position);
	m_Text.setPosition(position);
}

void Button::setTextString(const std::string& textString)
{
	m_Text.setString(textString);
	sf::FloatRect textRect = m_Text.getLocalBounds();
	m_Text.setOrigin(textRect.left + textRect.width / 2.0f,	textRect.top + textRect.height / 2.0f);
}

void Button::onFocusChanged()
{
	if (m_FocusState)
		increaseSize();
	else
		decreaseSize();
}

Button::~Button()
{
}
