#include "Overlay.h"

Overlay::Overlay(Vector2f position, Vector2f size, string text)
{
	m_sfVTopLeftPos = position;
	m_sfVSize = size;


	float scalex = size.x / 800;
	float scaley = size.y / 600;

	if (!m_sfTexture.loadFromFile("Assets/textures/popUp.png"))
	{
		cout << "Error: menuScreen.png was unable to load.";
	};
	
	//load font
	if (!m_sfFont.loadFromFile("Assets/fonts/arialbd.ttf"))
	{
		cout << "Error: Font ariali.ttf was unable to load.";
	};

	m_sfRect.setPosition(position.x, position.y);
	m_sfRect.setSize(size);

	
	m_sfSprite.setScale(Vector2f(scalex, scaley));
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setPosition(m_sfRect.getPosition().x , m_sfRect.getPosition().y );


	m_sfText.setFont(m_sfFont);
	m_sfText.setString(text);
	m_sfText.setCharacterSize(22);
	m_sfText.setFillColor(Color(0, 0, 0));
	m_sfText.setPosition(Vector2f(position.x + 25 , position.y + 25 ));
}

void Overlay::draw(RenderTarget & target, RenderStates states) const
{
	if (m_bDraw)
	{
		target.draw(m_sfSprite);
		target.draw(m_sfText);

	}

}

Overlay::Overlay()
{
}
