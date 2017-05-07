/**
*	@file SpriteRender.h
*	@class SpriteRender
*	@author Max Spencer-Hughes
*	@brief Sprite component
*	Sprite component used to contain the data (position, colour, rotation etc.) of sprites and buttons in the scene
*/

#pragma once

#include <Texture.h>
#include <GLSLProgram.h>
#include "Component.h"

namespace Component
{
class SpriteRenderer : public Component
	{
	private:
		GLuint quadVAO;
		void initRenderData();
		GLfloat vertices;
		glm::mat4 projection;

		std::shared_ptr<GLSLProgram> shader;
		std::shared_ptr<Texture> texture;
		glm::vec2 position;
		glm::vec2 size;
		GLfloat rotate;
		glm::vec3 color;
		glm::vec3 sID;

	public:
		SpriteRenderer();
		//~SpriteRenderer();

		GLfloat getVertices();
		GLint getVAO();
		glm::mat4 getProjection();
		std::shared_ptr<GLSLProgram> getShader();
		std::shared_ptr<Texture> getTexture();
		glm::vec2 getPosition();
		glm::vec2 getSize();
		GLfloat getRotate();
		glm::vec3 getColor();
		glm::vec3 getID();

		void setVAO(GLint VAO);
		void setProjection(glm::mat4 proj);
		void setShader(std::shared_ptr<GLSLProgram> shad);
		void setTexture(std::shared_ptr<Texture> tex);
		void setPosition(glm::vec2 pos);
		void setSize(glm::vec2 siz);
		void setRotate(GLfloat rot);
		void setColor(glm::vec3 colour);
		void setID(glm::vec3 id);

		//void DrawSprite(GLSLProgram &shader, Texture &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color);
	};
 }