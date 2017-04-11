
#pragma once
#include <stdafx.h>

// Std. Includes
#include <string>
#include <vector>
using namespace std;
// GL Includes
#include <gl\GL.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "aModel.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

aModel::aModel() {}

aModel::~aModel() {}


aModel::aModel(vector<aVertex> vertices, vector<GLuint> indices, vector<aTexture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

const vector<aVertex>& aModel::getVertex() {
	return this->vertices;
}

const vector<GLuint>& aModel::getIndices() {
	return this->indices;
}

const vector<aTexture>& aModel::getTexture() {
	return this->textures;
}

vector<glm::vec3> aModel::getPosition()
{
	vector<glm::vec3> pos;
	for (int it = 0; it != vertices.size(); ++it) {
		pos.push_back(vertices.at(it).Position);
	}
	return pos;
}

vector<glm::vec3> aModel::getNormal()
{
	vector<glm::vec3> norm;
	for (int it = 0; it != vertices.size(); ++it) {
		norm.push_back(vertices.at(it).Normal);
	}
	return norm;
}

vector<glm::vec2> aModel::getTexCoords()
{
	vector<glm::vec2> texc;
	for (int it = 0; it != vertices.size(); ++it) {
		texc.push_back(vertices.at(it).TexCoords);
	}
	return texc;
}