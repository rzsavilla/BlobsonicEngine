#include "stdafx.h"
#include "SpriteRender.h"

Component::SpriteRenderer::SpriteRenderer()
{
	initRenderData();
}

void Component::SpriteRenderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	gl::GenVertexArrays(1, &this->quadVAO);
	gl::GenBuffers(1, &VBO);
	gl::BindVertexArray(this->quadVAO);
	gl::BindBuffer(gl::ARRAY_BUFFER, VBO);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertices), vertices, gl::STATIC_DRAW);
	
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 4, gl::FLOAT, FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::BindVertexArray(0);
}

GLfloat Component::SpriteRenderer::getVertices()
{
	return vertices;
}

GLint Component::SpriteRenderer::getVAO()
{
	return quadVAO;
}

glm::mat4 Component::SpriteRenderer::getProjection()
{
	return projection;
}

std::shared_ptr<GLSLProgram> Component::SpriteRenderer::getShader()
{
	return shader;
}

std::shared_ptr<Texture> Component::SpriteRenderer::getTexture()
{
	return texture;
}

glm::vec2 Component::SpriteRenderer::getPosition()
{
	return position;
}

glm::vec2 Component::SpriteRenderer::getSize()
{
	return size;
}

GLfloat Component::SpriteRenderer::getRotate()
{
	return rotate;
}

glm::vec3 Component::SpriteRenderer::getColor()
{
	return color;
}

glm::vec3 Component::SpriteRenderer::getID()
{
	return sID;
}

void Component::SpriteRenderer::setVAO(GLint VAO)
{
	quadVAO = VAO;
}

void Component::SpriteRenderer::setProjection(glm::mat4 proj)
{
	projection = proj;
}

void Component::SpriteRenderer::setShader(std::shared_ptr<GLSLProgram> shad)
{
	shader = shad;
}

void Component::SpriteRenderer::setTexture(std::shared_ptr<Texture> tex)
{
	texture = tex;
}

void Component::SpriteRenderer::setPosition(glm::vec2 pos)
{
	position = pos;
}

void Component::SpriteRenderer::setSize(glm::vec2 siz)
{
	size = siz;
}

void Component::SpriteRenderer::setRotate(GLfloat rot)
{
	rotate = rot;
}

void Component::SpriteRenderer::setColor(glm::vec3 colour)
{
	color = colour;
}
void Component::SpriteRenderer::setID(glm::vec3 id)
{
	sID = id;
}

/*
void Component::SpriteRenderer::DrawSprite(GLSLProgram &shader, Texture &texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	// Prepare transformations
	shader.use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	//glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
	glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);

	//shader.setUniform("vertex", vertices);
	//shader.setUniform("projection", projection);
	shader.setUniform("spriteColor", color);
	shader.setUniform("model", model);

	// Set active texture
	// ...

	gl::BindVertexArray(this->quadVAO);
	gl::DrawArrays(gl::TRIANGLES, 0, 6);
	gl::BindVertexArray(0);
}
*/