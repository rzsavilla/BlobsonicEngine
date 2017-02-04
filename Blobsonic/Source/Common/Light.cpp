#include <stdafx.h>
#include "..\Include\Light.h"

Light::Light()
{
	m_vAmbient = glm::vec3(0.0f);
	m_vDiffuse = glm::vec3(0.0f);
	m_vSpecular = glm::vec3(0.0f);
	m_fRadius = 0.0f;
}

Light::Light(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float radius)
{
	setIntensity(Ambient, Diffuse, Specular,radius);
}

void Light::setPosition(glm::vec3 position)
{
	m_vPosition = position;
}

void Light::setPosition(float x, float y, float z)
{
	m_vPosition = glm::vec3(x, y, z);
}

void Light::setIntensity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular,float radius)
{
	m_vAmbient = Ambient;
	m_vDiffuse = Diffuse;
	m_vSpecular = Specular;
	m_fRadius = radius;
}

void Light::setAmbient(glm::vec3 Ambient)
{
	m_vAmbient = Ambient;
}

void Light::setDiffuse(glm::vec3 Diffuse)
{
	m_vDiffuse = Diffuse;
}

void Light::setSpecular(glm::vec3 Specular)
{
	m_vSpecular = Specular;
}

void Light::setAmbient(float Red, float Green, float Blue)
{
	m_vAmbient = glm::vec3(Red, Green, Blue);
}

void Light::setDiffuse(float Red, float Green, float Blue)
{
	m_vDiffuse = glm::vec3(Red, Green, Blue);
}

void Light::setSpecula(float Red, float Green, float Blue)
{
	m_vSpecular = glm::vec3(Red, Green, Blue);
}

void Light::setRadius(float radius)
{
	m_fRadius = radius;
}

glm::vec3 Light::getPosition() 
{
	return m_vPosition;
}

glm::vec3 Light::getAmbient() 
{
	return m_vAmbient;
}

glm::vec3 Light::getDiffuse() 
{
	return m_vDiffuse;
}

glm::vec3 Light::getSpecular() 
{
	return m_vSpecular;
}

float Light::getRadius()
{
	return m_fRadius;
}
