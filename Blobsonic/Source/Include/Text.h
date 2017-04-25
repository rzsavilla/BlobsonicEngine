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

//Freetype character
struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

namespace Component {
	class Text : public Component {
	private:
		std::string m_sText;	//!< String to be rendered
		glm::vec3 m_vPos;		//!< Screen Position/Relative/Origin (if transformable component is also attached)
		glm::vec4 m_vColour;	//!< Stores text colour RGBA;

		std::shared_ptr<GLSLProgram> m_shader;
		std::map<GLchar, Character>* m_ptrCharacters;	//!< Pointer to freetype character textures;
	
		GLuint m_VAO;	//!< Vertex Array Object
	public:
		Text();	//!< Default

		//! Set string Text to rendered
		void setString(std::string text);

		//! Set shader program to be used to render text
		void setShader(std::shared_ptr<GLSLProgram> shader);

		//! Pass buffer to OpenGL
		void buildBuffers();

		//! Get string Text
		std::string getString();
		//! Get Shader program
		std::shared_ptr<GLSLProgram> getShader();
		//! Get Vertex Array Object, required for rendering
		GLuint getVAO();
	};
}