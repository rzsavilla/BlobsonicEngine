
#include "stdafx.h"
#include "GUIButton.h"

Component::Button::Button()
{
	// Sets default (0) values for the button
	m_vScreenPosition = glm::vec2(0.0f, 0.0f);
	m_vSize = glm::vec2(0.0f, 0.0f);
}

void Component::Button::setPosition(glm::vec2 newPosition)
{
	m_vScreenPosition = newPosition;
}

void Component::Button::setPosition(float x, float y)
{
	m_vScreenPosition = glm::vec2(x, y);
}

void Component::Button::setSize(glm::vec2 newSize)
{
	m_vScreenPosition = newSize;
}

void Component::Button::setSize(float x, float y)
{
	m_vScreenPosition = glm::vec2(x, y);
}

void Component::Button::setClicked(bool click)
{
	isPressed = click;
}

