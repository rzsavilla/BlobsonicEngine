#include "stdafx.h"
#include "Button.h"
#include "SpriteRender.h"

Component::Button::Button()
{

}

bool Component::Button::getIsClicked()
{
	return m_bIsClicked;
}

int Component::Button::getButtonID()
{
	return m_iButtonID;
}

double Component::Button::getXPos()
{
	return xPos;
}

double Component::Button::getYPos()
{
	return yPos;
}

void Component::Button::setIsClicked(bool click)
{
	m_bIsClicked = click;
}

void Component::Button::setButtonID(int ID)
{
	m_iButtonID = ID;
}

void Component::Button::setPosition()
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	xPos = x;
	yPos = y;
}

