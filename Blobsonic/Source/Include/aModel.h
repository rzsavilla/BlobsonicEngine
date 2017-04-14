#pragma once
// Std. Includes
#include <string>
#include <vector>
using namespace std;
//#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct aVertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;

};

struct aTexture {
	GLint myId;
	string myType;
	aiString myPath;
};

class aModel {
public:
	//  Mesh Data
	vector<aVertex> vertices;
	vector<GLuint> indices;
	vector<aTexture> textures;

	//  Functions
	// Constructor
	aModel(vector<aVertex> vertices, vector<GLuint> indices, vector<aTexture> textures);
	aModel();
	~aModel();

	const vector<aVertex>& getVertex();
	const vector<GLuint>& getIndices();
	const vector<aTexture>& aModel::getTexture();

	vector<glm::vec3> getPosition();
	vector<glm::vec3> getNormal();
	vector<glm::vec2> aModel::getTexCoords();
private:
};
