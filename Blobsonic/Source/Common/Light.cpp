#include <stdafx.h>
#include "..\Include\Light.h"

Component::Light::Light()
{
	m_vAmbient = glm::vec3(0.0f);
	m_vDiffuse = glm::vec3(0.0f);
	m_vSpecular = glm::vec3(0.0f);
}

Component::Light::Light(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
{
	setIntensity(Ambient, Diffuse, Specular);
}

void Component::Light::setIntensity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
{
	m_vAmbient = Ambient;
	m_vDiffuse = Diffuse;
	m_vSpecular = Specular;
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

void Component::Light::setSpecular(float Red, float Green, float Blue)
{
	m_vSpecular = glm::vec3(Red, Green, Blue);
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
