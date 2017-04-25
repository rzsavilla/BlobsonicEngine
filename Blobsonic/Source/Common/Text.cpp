#include "stdafx.h"
#include "Text.h"

Component::Text::Text()
{

}

void Component::Text::setString(std::string text)
{
	m_sText = text;
}

void Component::Text::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_shader = shader;
}

std::string Component::Text::getString()
{
	return m_sText;
}

std::shared_ptr<GLSLProgram> Component::Text::getShader()
{
	return m_shader;
}

GLuint Component::Text::getVAO()
{
	return m_VAO;
}

void Component::Text::buildBuffers()
{
	GLuint VBO;

	gl::GenVertexArrays(1, &m_VAO);
	gl::GenBuffers(1, &VBO);

	//Bind Buffers
	gl::BindVertexArray(m_VAO);
	gl::BindBuffer(gl::ARRAY_BUFFER,VBO);

	gl::BufferData(gl::ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, gl::DYNAMIC_DRAW);
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 4 * sizeof(GLfloat), 0);
	
	//Unbind Buffers
	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::BindVertexArray(0);
};
