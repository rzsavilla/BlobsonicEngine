#include <stdafx.h>
#include "..\Include\Light.h"

Component::Light::Light()
{
	m_vAmbient = glm::vec3(0.0f);
	m_vDiffuse = glm::vec3(0.0f);
	m_vSpecular = glm::vec3(0.0f);
	m_fRadius = 0.0f;
}

Component::Light::Light(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float radius)
{
	setIntensity(Ambient, Diffuse, Specular,radius);
}

void Component::Light::setType(LightType type)
{
	m_type = type;
}

void Component::Light::setIntensity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular,float radius)
{
	m_vAmbient = Ambient;
	m_vDiffuse = Diffuse;
	m_vSpecular = Specular;
	m_fRadius = radius;
}

void Component::Light::setAmbient(glm::vec3 Ambient)
{
	m_vAmbient = Ambient;
}

void Component::Light::setDiffuse(glm::vec3 Diffuse)
{
	m_vDiffuse = Diffuse;
}

void Component::Light::setSpecular(glm::vec3 Specular)
{
	m_vSpecular = Specular;
}

void Component::Light::setAmbient(float Red, float Green, float Blue)
{
	m_vAmbient = glm::vec3(Red, Green, Blue);
}

void Component::Light::setDiffuse(float Red, float Green, float Blue)
{
	m_vDiffuse = glm::vec3(Red, Green, Blue);
}

void Component::Light::setSpecula(float Red, float Green, float Blue)
{
	m_vSpecular = glm::vec3(Red, Green, Blue);
}

void Component::Light::setRadius(float radius)
{
	m_fRadius = radius;
}

void Component::Light::setDirection(glm::vec3 newDirection)
{
	m_vDirection = glm::normalize(newDirection);
}

LightType Component::Light::getType()
{
	return m_type;
}

glm::vec3 Component::Light::getAmbient()
{
	return m_vAmbient;
}

glm::vec3 Component::Light::getDiffuse()
{
	return m_vDiffuse;
}

glm::vec3 Component::Light::getSpecular()
{
	return m_vSpecular;
}

float Component::Light::getRadius()
{
	return m_fRadius;
}

glm::vec3 Component::Light::getDirection()
{
	return m_vDirection;
}
