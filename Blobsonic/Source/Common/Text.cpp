#include "stdafx.h"
#include "Text.h"

Component::Text::Text()
{
	//buildBuffers();

	if (!m_bCharSet) {
		// FreeType
		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// Load font as face
		FT_Face face;
		if (FT_New_Face(ft, "Source/Resources/fonts/arial.ttf", 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disable byte-alignment restriction
		gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);

		std::map<GLchar, Character> Characters;

		gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			gl::GenTextures(1, &texture);
			gl::BindTexture(gl::TEXTURE_2D, texture);
			gl::TexImage2D(
				gl::TEXTURE_2D,
				0,
				gl::RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				gl::RED,
				gl::UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
			gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
			gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
			gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			m_ptrCharacters.insert(std::pair<GLchar, Character>(c, character));
			m_bCharSet = true;
		}
	}
}

void Component::Text::setString(std::string text)
{
	m_sText = text;
}

void Component::Text::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_shader = shader;
}

void Component::Text::setColour(glm::vec4 colour)
{
	m_vColour = colour;
}

void Component::Text::setPosition(glm::vec3 pos)
{
	m_vPos = pos;
}

void Component::Text::setCharacters(std::map<GLchar, Character> ptrCharacters)
{
	m_ptrCharacters = ptrCharacters;
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

glm::vec4 Component::Text::getColour()
{
	return m_vColour;
}

glm::vec3 Component::Text::getPosition()
{
	return m_vPos;
}

std::map<GLchar, Character> Component::Text::getCharactersPtr()
{
	return m_ptrCharacters;
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
