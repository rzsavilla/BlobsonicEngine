#include "stdafx.h"
#include "Particle.h"

Component::Particle::Particle()
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	velocity.z = 0.0f;
	acceleration.x = 0.0f;
	acceleration.y = 0.0f;
	acceleration.z = 0.0f;

	hasCollisions = true;
	mass = 1.0f;
	minScale = 1.0f;
	maxScale = 1.0f;

	isDead = false;

	
}

void Component::Particle::setPosition(glm::vec3 pos)
{
	position = pos;
}

void Component::Particle::setLookAt(glm::vec3 lkat)
{
	lookAt = lkat;
}

void Component::Particle::setVelocity(glm::vec3 vel)
{
	velocity = vel;
}

void Component::Particle::setAcceleration(glm::vec3 acc)
{
	acceleration = acc;
}

void Component::Particle::setHasCollisions(bool state)
{
	hasCollisions = state;
}

void Component::Particle::setMass(float m)
{
	mass = m;
}

void Component::Particle::setMinScale(float minS)
{
	minScale = minS;
}

void Component::Particle::setMaxScale(float maxS)
{
	maxScale = maxS;
}

void Component::Particle::setNumMax(float numM)
{
	numParticles = numM;
	particleMatrices = new glm::mat4[numM];
	
}

void Component::Particle::setDead(bool state)
{
	isDead = state;
}

void Component::Particle::setMesh(std::shared_ptr<AssimpMesh> mesh)
{
	m_particleMesh = mesh;
}

void Component::Particle::setShader(std::shared_ptr<GLSLProgram> shad)
{
	m_shader = shad;
}

void Component::Particle::setTexture(std::shared_ptr<Texture> tex)
{
	m_texture = tex;
}

void Component::Particle::setMaterial(std::shared_ptr<Material> mat)
{
	m_material = mat;
}

void Component::Particle::setBuffers()
{
	GLuint buffer;
	std::shared_ptr<AssimpMesh> m_aMesh = this->getMesh();

	gl::GenBuffers(1, &buffer);
	gl::BindBuffer(gl::ARRAY_BUFFER, buffer);
	glm::mat4* matrix = this->getMatrix();
	gl::BufferData(gl::ARRAY_BUFFER, this->getNumMax() * sizeof(glm::mat4), &matrix[0], gl::STATIC_DRAW);

	gl::BindVertexArray(m_aMesh->getVAO());		//Bind VAO
	gl::EnableVertexAttribArray(5);
	gl::VertexAttribPointer(5, 4, gl::FLOAT, FALSE, sizeof(glm::mat4), (GLvoid*)0);
	gl::EnableVertexAttribArray(6);
	gl::VertexAttribPointer(6, 4, gl::FLOAT, FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
	gl::EnableVertexAttribArray(7);
	gl::VertexAttribPointer(7, 4, gl::FLOAT, FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
	gl::EnableVertexAttribArray(8);
	gl::VertexAttribPointer(8, 4, gl::FLOAT, FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

	gl::VertexAttribDivisor(5, 1);
	gl::VertexAttribDivisor(6, 1);
	gl::VertexAttribDivisor(7, 1);
	gl::VertexAttribDivisor(8, 1);
}

void Component::Particle::setMatrix(glm::mat4 * mat)
{
	particleMatrices = mat;
}

glm::vec3 Component::Particle::getPosition()
{
	return position;
}

glm::vec3 Component::Particle::getLookAt()
{
	return lookAt;
}

glm::vec3 Component::Particle::getVelocity()
{
	return velocity;
}

glm::vec3 Component::Particle::getAcceleration()
{
	return acceleration;
}

glm::mat4* Component::Particle::getMatrix()
{
	return particleMatrices;
}

bool Component::Particle::getHasCollisions()
{
	return hasCollisions;
}

float Component::Particle::getMass()
{
	return mass;
}

float Component::Particle::getMinScale()
{
	return minScale;
}

float Component::Particle::getMaxScale()
{
	return maxScale;
}

float Component::Particle::getNumMax()
{
	return numParticles;
}

bool Component::Particle::getDead()
{
	return isDead;
}

std::shared_ptr<AssimpMesh> Component::Particle::getMesh()
{
	return m_particleMesh;
}

std::shared_ptr<GLSLProgram> Component::Particle::getShader()
{
	return m_shader;
}

std::shared_ptr<Texture> Component::Particle::getTexture()
{
	return m_texture;
}

std::shared_ptr<Material> Component::Particle::getMaterial()
{
	return m_material;
}
