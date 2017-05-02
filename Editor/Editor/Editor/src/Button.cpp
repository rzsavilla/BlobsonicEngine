#include "Button.h"

Button::Button()
{
}

Button::Button(string text, Vector2f pos, Vector2f size, Vector2f resolutionScale, string textureName)
{

	m_sButtonText = text;
	float scalex = size.x / 400 ;
	float scaley = size.y / 118 ;


	float textScale = min(scalex, scaley);
	m_sfResolutionScale = resolutionScale;

	m_sfVTopLeftPos = pos;
	m_sfVSize = size;
	if (!m_sfTexture.loadFromFile("Assets/textures/" + textureName + ".png"))
	{
		cout << "Error: " + textureName + ".png was unable to load.";
	};

	//load font
	if (!m_sfFont.loadFromFile("Assets/fonts/ARIALN.ttf"))
	{
		cout << "Error: Font ariali.ttf was unable to load.";
	};

	m_sfRect.setPosition(m_sfVTopLeftPos.x, m_sfVTopLeftPos.y);
	m_sfRect.setSize(size);


	m_sfSprite.setScale(Vector2f(scalex, scaley));
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setPosition(m_sfRect.getPosition().x , m_sfRect.getPosition().y );
	
	float numChar = m_sButtonText.getSize();
	float xpos = (m_sfVTopLeftPos.x + (m_sfVSize.x / 2) - numChar * 7 *textScale * m_sfResolutionScale.x);
	float ypos = (m_sfVTopLeftPos.y + m_sfVSize.y / 2) - 30 * textScale  * m_sfResolutionScale.y;

	// Create a text

	float fSize = 30 * textScale * m_sfResolutionScale.x;
	if (fSize < 15)fSize = 15;

	m_sfButtonText = Text(m_sButtonText, m_sfFont);
	m_sfButtonText.setCharacterSize(fSize);
	m_sfButtonText.setStyle(Text::Bold);
	m_sfButtonText.setFillColor(Color(0, 0, 0));
	m_sfButtonText.setPosition(Vector2f(xpos, ypos));

}

void Button::setText(string text)
{
	m_sButtonText = text;
	float scalex = m_sfVSize.x / 400;
	float scaley = m_sfVSize.y / 118;
	float textScale = scalex / scaley;

	float numChar = m_sButtonText.getSize();
	float xpos = ((m_sfVTopLeftPos.x + (m_sfVSize.x / 2) - numChar * 7 * textScale ) * m_sfResolutionScale.x);
	float ypos = ((m_sfVTopLeftPos.y + m_sfVSize.y / 2) - 30 * textScale ) * m_sfResolutionScale.y;

	// Create a text
	m_sfButtonText = Text(m_sButtonText, m_sfFont);
	m_sfButtonText.setCharacterSize(30 * textScale * m_sfResolutionScale.x);
	m_sfButtonText.setStyle(Text::Bold);
	m_sfButtonText.setFillColor(Color(0, 0, 0));
	m_sfButtonText.setPosition(Vector2f(xpos, ypos));
}



void Button::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfSprite);
	target.draw(m_sfButtonText);
}
