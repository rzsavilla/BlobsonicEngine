#include <stdafx.h>
#include "Text.h"

/*
	Tutorial: https://learnopengl.com/#!In-Practice/Text-Rendering
	Freetype: https://www.freetype.org/
*/
/*
Text::Text(std::string string, std::map<GLchar, Character>* characters, float x, float y, glm::vec3 colour, float scale)
{
	m_string = string;
	m_vPos.x = x;
	m_vPos.y = y;
	m_vColour = colour;
	m_fScale = scale;
	m_ptrCharacters = characters;

	// Configure VAO/VBO for texture quads
	gl::GenVertexArrays(1, &VAO);
	gl::GenBuffers(1, &VBO);
	gl::BindVertexArray(VAO);
	gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, gl::DYNAMIC_DRAW);
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 4 * sizeof(GLfloat), 0);
	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::BindVertexArray(0);
}

void Text::setString(std::string string)
{
	m_string = string;
}

void Text::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_shader = shader;
}

void Text::draw()
{
	// Activate corresponding render state	
	m_shader->use();
	m_shader->setUniform("textColor", m_vColour.x, m_vColour.y, m_vColour.z);
	m_shader->setUniform("projection", glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f));
	//m_shader->setUniform("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindVertexArray(VAO);
	GLfloat x = m_vPos.x;
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = m_string.begin(); c != m_string.end(); c++)
	{
		Character ch = m_ptrCharacters->at(*c);

		GLfloat xpos = x + ch.Bearing.x * m_fScale;
		GLfloat ypos = m_vPos.y - (ch.Size.y - ch.Bearing.y) * m_fScale;

		GLfloat w = ch.Size.x * m_fScale;
		GLfloat h = ch.Size.y * m_fScale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		gl::BindTexture(gl::TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
		gl::BufferSubData(gl::ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
		gl::BindBuffer(gl::ARRAY_BUFFER, 0);
		// Render quad
		gl::DrawArrays(gl::TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * m_fScale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	gl::BindVertexArray(0);
	gl::BindTexture(gl::TEXTURE_2D, 0);
}
*/