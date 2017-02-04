#pragma once

#include "stdafx.h"

class Graphics {
private:
	int width, height;
	GLuint vboHandles[3];

	GLuint vaoHandle;
	

	void linkMe(GLint vertShader, GLint fragShader);
	GLuint indexSize;
	GLuint numberOfIndices;
	GLuint indices;

	glm::mat4 M;	//Model matrix
	glm::mat4 V;	//View matrix
	glm::mat4 P;	//Projection matrix

	float rot = 0;

public:
	Graphics();
	GLuint programHandle;
	void init();
	void update(float t);
	void render();
	void resize(int, int);
};