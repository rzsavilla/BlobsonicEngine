/**
* @class	Mesh
* @brief	Mesh loaded from obj file 
* Stores objects vertices, indices, normals, texture coordinates, will also parse the obj file
*/

#pragma once

#include <stdafx.h>
#include "ID.h"

class Mesh {
private:
	std::vector<GLfloat> vf_vertices;		//Store models vertices
	std::vector<GLuint> vi_vertIndices;		//Store model vertex indices
	
	std::vector<GLfloat> vf_vertNormals;	//Stores vertex normals;
	std::vector<GLuint> vi_vertNormIndices;	//Stores normal indices
	std::vector<GLfloat> vf_textCoords;		//Stores texture coordinates
	std::vector<GLuint> vi_textIndices;		//Stores texture indices

	std::vector<GLfloat> vf_expandedVertices;	//Expanded vertices
	std::vector<GLfloat> vf_expandedTexCoords;	//Expanded texture coordinates
	std::vector<GLfloat> vf_expandedNormals;	//Expanded vertex normals;

	GLuint m_VAO;
	GLuint m_handle[3];

	void setBuffers();
public:
	Mesh();	//!< Default Constructor
	Mesh(std::string sFilename);	//!< Constructor set to parse obj file
	bool load(std::string sFilename);	//!< Parse obj file

	void setVAO(GLuint vao);
	GLuint getVAO();
	
	const std::vector<GLfloat>& getVertNormals();			//!< Returns reference to vertex normals
	const std::vector<GLuint>& getVertNormIndices();		//!< Returns reference to vertex normals indices
	const std::vector<GLfloat>& getTextCoords();			//!< Returns reference to texture coordinates
	const std::vector<GLuint>& getTextIndices();			//!< Returns reference to texture coordinates indices

	const std::vector<GLfloat>& getVertices();				//!< Returns mesh vertices
	const std::vector<GLuint>& getVertIndices();			//!< Returns mesh vertex indices

	const std::vector<GLfloat>& getExpandedVertices();		//!< Returns expanded vertices
	const std::vector<GLfloat>& getExpandedTexCoords();		//!< Returns expanded texture coordinates
	const std::vector<GLfloat>& getExpandedNormals();		//!< Returns expanded vertex normals
};