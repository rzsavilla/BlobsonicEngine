/**
* @class	Text
* @brief	Render text onto the window
* Renders text using freetype
* The Scene stores game objects, and updates objects and game logic.
*/

/*
	Tutorial: https://learnopengl.com/#!In-Practice/Text-Rendering
	Freetype: https://www.freetype.org/
*/

#pragma once

#include "Drawable.h"

/*

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class Text :public Drawable {
private:
	std::string m_string;			//!< String that is rendered
	glm::vec2 m_vPos;				//!< Text position
	glm::vec3 m_vColour;			//!< Text colour
	std::shared_ptr<GLSLProgram> m_shader;	//!< Shader used to draw text
	float m_fScale;					//!< Text Scale
	std::map<GLchar, Character>* m_ptrCharacters;	//!< Pointer to freetype characters texture used to draw text

	GLuint VAO, VBO;		//!< Vertex array buffer and Vertex buffer object index to opengl data buffer
public:
	//! Default constructor
	Text(std::string string, std::map<GLchar, Character>* characters, float x, float y, glm::vec3 colour, float scale);

	void setString(std::string string);		//!< Set string to be rendered

	void setShader(std::shared_ptr<GLSLProgram> shader);	//!< Set shader used to draw text

	void draw();	//!< Draw text
};

*/
