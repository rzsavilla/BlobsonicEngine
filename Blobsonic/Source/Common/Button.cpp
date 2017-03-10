#include <stdafx.h>
#include "Button.h"

//Button::Button(){}

void Button::initButton(Mesh* CubeMesh)
{
	m_buttonModel.setMesh(CubeMesh);
	m_buttonModel.setOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	m_buttonModel.setScale(glm::vec3(20.0f, 10.0f, 0.0f));

	

	m_buttonModel.setRotation(15.0f, xAxis);
	m_buttonModel.setRotation(-15.0f, zAxis);
	m_buttonModel.setRotation(45.0f, yAxis);

	m_vCameraPos = m_Camera.position();
	m_vCameraProj = m_Camera.projection();

	x = 20.0f;
	y = 10.0f;
	z = -20.0f;
};

Button::Button(Mesh* CubeMesh)
{
	printf("Button Here, Hello World!");

	initButton(CubeMesh);
}

Button::~Button()
{

}

void Button::setPosition(glm::vec2 newPos)
{ // Sets the position of the button

}

void Button::setColour(glm::vec3 newColour)
{ // Set the colour of the button
	//vec3 colour = vec3(1.0f, 0.0f, 1.0f); //Pink

	//m_ptrShader->use();
	//m_ptrShader->setUniform("myColour", colour); 
}

void Button::setText()
{ // Set the text on the button
  //Create button text
  //m_ButtonText = std::make_shared<Text>("Click Me!", m_ptrCharacters, 350.0f, 400.0f, glm::vec3(0.0f, 0.0f, 0.0f), 2.0f);
  //m_ButtonText->setShader(m_ptrResources->getShader("text_shader"));
}

void Button::draw()
{// Drawn the button using OpenGL
	// Position
	glm::vec3 pos = glm::vec3(x, y, z);;
	m_buttonModel.setPosition(pos);

	// Colour
	vec3 colour = vec3(0.0f, 1.0f, 0.0f); //teal
	m_ptrShader->use();
	m_ptrShader->setUniform("myColour", colour);
	
	m_buttonModel.draw();
}

void Button::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_ptrShader = shader;
	m_buttonModel.setShader(m_ptrShader);
}

void Button::setMaterial(Material * material)
{
	m_ptrMaterial = material;
	m_buttonModel.setMaterial(m_ptrMaterial);
}

std::shared_ptr<GLSLProgram> Button::getShader()
{
	return m_buttonModel.getShader();
}

bool Button::collision(glm::vec2 point)
{
	return false;
}
