/**
* @class	Text
* @brief	Contains data for rendering text onto window
* @author	Rozen Savilla 
* Renders text using freetype onto window, gives entity variables required for rendering text
*/

/*
Tutorial: https://learnopengl.com/#!In-Practice/Text-Rendering
Freetype: https://www.freetype.org/
*/
#pragma once

#include "stdafx.h"
#include "Component.h"

#include "GLSLProgram.h"

// FreeType 2
#include <ft2build.h>
#include FT_FREETYPE_H

//Freetype character
struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

static std::map<GLchar, Character> m_ptrCharacters = std::map<GLchar, Character>();;	//!< Pointer to freetype character textures;

namespace Component {
	class Text : public Component {
	private:
		std::string m_sText;	//!< String to be rendered
		glm::vec3 m_vPos;		//!< Screen Position/Relative/Origin (if transformable component is also attached)
		glm::vec4 m_vColour;	//!< Stores text colour RGBA;

		std::shared_ptr<GLSLProgram> m_shader;
		bool m_bCharSet = false;
	
		GLuint m_VAO;	//!< Vertex Array Object
	public:
		Text();	//!< Default

				//! Pass buffer to OpenGL
		void buildBuffers();

		//! Set string Text to rendered
		void setString(std::string text);
		//! Set shader program to be used to render text
		void setShader(std::shared_ptr<GLSLProgram> shader);
		//! Set the colour of the text to be rendered
		void setColour(glm::vec4 colour);
		//! Set the position of the text to be rendered
		void setPosition(glm::vec3 pos);

		
		//! Set character textures for
		void setCharacters(std::map<GLchar, Character> ptrCharacters);

		//! Get string Text
		std::string getString();
		//! Get Shader program
		std::shared_ptr<GLSLProgram> getShader();
		//! Get Vertex Array Object, required for rendering
		GLuint getVAO();
		//! Get vector of colours
		glm::vec4 getColour();
		//! Get vector of position
		glm::vec3 getPosition();

		std::map<GLchar, Character> getCharactersPtr();
	};
}