#pragma once

#include "Drawable.h"

class Button: public Drawable{
private:
	glm::vec2 m_vPosition;
	glm::vec3 m_vColour;
	std::string m_sString;

public:
	Button();

	void setPosition(glm::vec2 newPos);
	void setColour(glm::vec3 newColour);
	void setText();

	void draw();

	bool collision(glm::vec2 point);
};