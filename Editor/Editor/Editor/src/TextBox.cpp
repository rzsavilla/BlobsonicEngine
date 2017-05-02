#include "TextBox.h"

TextBox::TextBox()
{
}

TextBox::TextBox(string text, Vector2f pos, Vector2f size, string textureName)
{

	float scalex = size.x / 343;
	float scaley = size.y / 37;

	m_sDefaultText = "";

	m_sfVTopLeftPos = pos;
	m_sfVSize = size;

	if (!m_sfTexture.loadFromFile("Assets/textures/" + textureName + ".png"))
	{
		cout << "Error: " + textureName + ".png was unable to load.";
	};

	//load font
	if (!m_sfFont.loadFromFile("Assets/fonts/arial.ttf"))
	{
		cout << "Error: Font ariali.ttf was unable to load.";
	};

	m_sfRect.setPosition(m_sfVTopLeftPos.x, m_sfVTopLeftPos.y);
	m_sfRect.setSize(size);


	m_sfSprite.setScale(Vector2f(scalex, scaley));
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setPosition(m_sfRect.getPosition().x, m_sfRect.getPosition().y);

	m_sfButtonText.setFont(m_sfFont);
	m_sfButtonText.setString(text);
	m_sfButtonText.setCharacterSize(30);
	m_sfButtonText.setFillColor(Color(0, 0, 0));
	m_sfButtonText.setPosition(Vector2f(pos.x + 10 , pos.y ));
	
}


TextBox::TextBox(string defaultText, string text, Vector2f pos, Vector2f size, string textureName)
{

	float scalex = size.x / 343;
	float scaley = size.y / 37;

	m_sDefaultText = defaultText;

	m_sfVTopLeftPos = pos;
	m_sfVSize = size;

	if (!m_sfTexture.loadFromFile("Assets/textures/" + textureName + ".png"))
	{
		cout << "Error: " + textureName + ".png was unable to load.";
	};

	//load font
	if (!m_sfFont.loadFromFile("Assets/fonts/arial.ttf"))
	{
		cout << "Error: Font ariali.ttf was unable to load.";
	};

	m_sfRect.setPosition(m_sfVTopLeftPos.x, m_sfVTopLeftPos.y);
	m_sfRect.setSize(size);


	m_sfSprite.setScale(Vector2f(scalex, scaley));
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setPosition(m_sfRect.getPosition().x, m_sfRect.getPosition().y);

	m_sfButtonText.setFont(m_sfFont);
	m_sfButtonText.setString(m_sDefaultText + text);
	m_sfButtonText.setCharacterSize(30);
	m_sfButtonText.setFillColor(Color(0, 0, 0));
	m_sfButtonText.setPosition(Vector2f(pos.x + 10, pos.y));

}

TextBox::~TextBox()
{
}

void TextBox::takeInput(Keyboard::Key pressedKey)
{
	if (m_bIsEntering == true)
	{
	
		char input;
		if (pressedKey == Keyboard::Return)
		{
			m_bIsEntering = false;
			return;
		}
		if (pressedKey == Keyboard::BackSpace || pressedKey == Keyboard::Delete)
		{
			m_sText = "";
			m_sfButtonText.setString(m_sDefaultText + m_sText);
			return;
		}
		if (pressedKey >= 0 && pressedKey < 26)
		{
			input = pressedKey + 97;
			stringstream ss;
			ss << input;
			string s;
			ss >> s;

			m_sText = m_sText + s;
			m_sfButtonText.setString(m_sDefaultText + m_sText);
		}
		if (pressedKey > 25 && pressedKey < 36	)
		{
			input = pressedKey + 22;
			stringstream ss;
			ss << input;
			string s;
			ss >> s;

			m_sText = m_sText + s;
			m_sfButtonText.setString(m_sDefaultText + m_sText);
		}

		

	
	}
}

void TextBox::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfSprite);
	target.draw(m_sfButtonText);
}
