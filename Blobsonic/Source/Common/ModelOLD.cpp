#include <stdafx.h>
#include "ModelOLD.h"

#include <../glm/gtc/type_ptr.hpp>

void Model::setBuffers()
{
	gl::BindVertexArray(VAO);

	//Place data in buffers
	// Vertex position
	//Use expanded vertices and texture coordinates if it has a texture

	//Mesh with UVs
	if (!m_ptrMesh->getExpandedTexCoords().empty() && m_ptrTexture) {
		//Expanded Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, (m_ptrMesh->getExpandedVertices().size()) * sizeof(GLfloat), m_ptrMesh->getExpandedVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		//Expanded Texture Coordinates
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
		gl::BufferData(gl::ARRAY_BUFFER, m_ptrMesh->getExpandedTexCoords().size() * sizeof(GLfloat), m_ptrMesh->getExpandedTexCoords().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(1);

		//Normals
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, (m_ptrMesh->getExpandedNormals().size()) * sizeof(GLfloat), m_ptrMesh->getExpandedNormals().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(2);
	}
	//Mesh with normals but no UVs
	else if (!m_ptrMesh->getExpandedNormals().empty()) {
		//Expanded Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, (m_ptrMesh->getExpandedVertices().size()) * sizeof(GLfloat), m_ptrMesh->getExpandedVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		//Normals
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, (m_ptrMesh->getExpandedNormals().size()) * sizeof(GLfloat), m_ptrMesh->getExpandedNormals().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(2);
	}
	//Use Element Array buffer (Indices) 
	else {
		//Vertices
		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, (m_ptrMesh->getVertices().size()) * sizeof(GLfloat), m_ptrMesh->getVertices().data(), gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
		gl::EnableVertexAttribArray(0);

		// Indices
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, EBO);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (m_ptrMesh->getVertIndices().size()) * sizeof(GLfloat), m_ptrMesh->getVertIndices().data(), gl::STATIC_DRAW);
	}

	gl::BindVertexArray(0);		//Unbind
}

void Model::setMesh(Mesh * newMesh, Texture* newTexture)
{
	m_ptrMesh = newMesh;
	m_ptrTexture = newTexture;
	setBuffers();
}

void Model::setMaterial(Material * material)
{
	m_ptrMaterial = material;
}

void Model::setTexture(Texture* texture)
{
	m_ptrTexture = texture;
	setBuffers();
}

void Model::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_ptrShader = shader;
}

void Model::setPosition(glm::vec3 newPos)
{
	m_vPosition = newPos;
	t = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		newPos.x, newPos.y, newPos.z, 1.0f
	);
}

void Model::setScale(glm::vec3 newScale)
{
	m_vScale = newScale;
	s = glm::mat4(
		newScale.x, 0.0f, 0.0f, 0.0f,
		0.0f, newScale.y, 0.0f, 0.0f,
		0.0f, 0.0f, newScale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Model::setRotation(float degrees, Axis axis)
{
	float rad = glm::radians(degrees);
	switch (axis)	//Choose axis to rotate around
	{
	case xAxis:
		r = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(rad), -sin(rad), 0.0f,
			0.0f, sin(rad), cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case yAxis:
		r = glm::mat4(
			cos(rad), 0.0f, sin(rad), 0.0f,
			0, 1.0, 0.0f, 0.0f,
			-sin(rad), 0.0f, cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case zAxis:
		r = glm::mat4(
			cos(rad), -sin(rad), 0.0f, 0.0f,
			sin(rad), cos(rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	default:
		break;
	}
}

std::shared_ptr<GLSLProgram> Model::getShader()
{
	return m_ptrShader;
}

void Model::translate(glm::vec3 translate)
{
	t *= glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f
	);
	//m_vPosition = glm::vec3(t[3].x, t[3].y, t[3].z);	//Update position
	m_vPosition = (glm::vec3) t[3];
}

void Model::setOrigin(glm::vec3 newOrigin)
{
	m_vOrigin = newOrigin;
}

glm::vec3 Model::getPosition()
{
	return m_vPosition;
}

glm::vec3 Model::getScale()
{
	return m_vScale;
}

glm::mat4 Model::getTransform()
{
	glm::mat4 translate,rotate,s, o, originMinus;

	translate = t;
	rotate = r;

	o = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		m_vOrigin.x, m_vOrigin.y, m_vOrigin.z, 1.0f
	);

	s = glm::mat4(
		m_vScale.x, 0.0f, 0.0f, 0.0f,
		0.0f, m_vScale.y, 0.0f, 0.0f,
		0.0f, 0.0f, m_vScale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	//Scale -> translate to origin -> rotate -> translate to position
	//Translates to origin first in order to cause rotation around that origin
	return t * r * o * s;
}

void Model::rotate(float degrees, Axis Axis)
{
	glm::mat4 s = r;

	float rad = glm::radians(degrees);
	switch (Axis)	//Choose axis to rotate around
	{
	case xAxis:
		r *= glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(rad), -sin(rad), 0.0f,
			0.0f, sin(rad), cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case yAxis:
		r *= glm::mat4(
			cos(rad), 0.0f, sin(rad), 0.0f,
			0, 1.0, 0.0f, 0.0f,
			-sin(rad), 0.0f, cos(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	case zAxis:
		r *= glm::mat4(
			cos(rad), -sin(rad), 0.0f, 0.0f,
			sin(rad), cos(rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		break;
	default:
		break;
	}
}

Model::Model()
{
	//Generate Buffer handles
	gl::GenVertexArrays(1, &VAO);

	gl::GenBuffers(3, handle);

	gl::GenBuffers(1, &VBO[0]);
	gl::GenBuffers(1, &VBO[1]);
	gl::GenBuffers(1, &EBO);

	 t = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	 r = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	s = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_vOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Model::draw()
{
	m_ptrShader->use();	//Ensure correct shader is used

	m_ptrShader->setUniform("mModel", getTransform());	//Pass model transformation matrix

	//Material reflectivity
	if (m_ptrMaterial != NULL) {	//Has material
		m_ptrShader->setUniform("Ka", m_ptrMaterial->getAmbient());		//Ambient material reflection
		m_ptrShader->setUniform("Kd", m_ptrMaterial->getDiffuse());		//Diffuse
		m_ptrShader->setUniform("Ks", m_ptrMaterial->getSpecular());		//Specular
		m_ptrShader->setUniform("shininess", m_ptrMaterial->getShininess());
	}

	///////////Draw Mesh////////////////////////
	if (m_ptrMesh != NULL) {		//Has pointer to mesh
		//Has Texture
		if ((!m_ptrMesh->getExpandedTexCoords().empty() && !m_ptrTexture == NULL)) {
			gl::BindVertexArray(this->VAO);
			gl::BindTexture(gl::TEXTURE_2D, m_ptrTexture->object());					//Bind Texture
			gl::DrawArrays(gl::TRIANGLES, 0, m_ptrMesh->getExpandedVertices().size());
			gl::BindVertexArray(0);					//Unbind VAO
			gl::BindTexture(gl::TEXTURE_2D, 0);		//Unbind Texture	
		}
		else if (!m_ptrMesh->getExpandedNormals().empty()) {
			gl::BindVertexArray(this->VAO);
			gl::DrawArrays(gl::TRIANGLES, 0, m_ptrMesh->getExpandedVertices().size());
			gl::BindVertexArray(0);				//Unbind VAO
		}
		else {
			gl::BindVertexArray(this->VAO);
			gl::DrawElements(gl::TRIANGLES, m_ptrMesh->getVertIndices().size(), gl::UNSIGNED_INT, 0);
			gl::BindVertexArray(0);				//Unbind VAO
		}
	}
}