#include <stdafx.h>
#include "Material.h"

Material::Material()
{
	m_vAmbientReflect = glm::vec3(0.0f);
	m_vDiffuseReflect = glm::vec3(0.0f);
	m_vSpecularReflect = glm::vec3(0.0f);
}

Material::Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float shininess)
{
	setReflectivity(Ambient, Diffuse, Specular, shininess);
}

void Material::setReflectivity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float shininess)
{
	m_vAmbientReflect = Ambient;
	m_vDiffuseReflect = Diffuse;
	m_vSpecularReflect = Specular;
	m_fShininess = shininess;
}

void Material::setAmbient(glm::vec3 Ambient)
{
	m_vAmbientReflect = Ambient;
}

void Material::setDiffuse(glm::vec3 Diffuse)
{
	m_vDiffuseReflect = Diffuse;
}

void Material::setSpecular(glm::vec3 Specular)
{
	m_vSpecularReflect = Specular;
}

void Material::setAmbient(float Red, float Green, float Blue)
{
	m_vAmbientReflect = glm::vec3(Red, Green, Blue);
}

void Material::setDiffuse(float Red, float Green, float Blue)
{
	m_vDiffuseReflect = glm::vec3(Red, Green, Blue);
}

void Material::setSpecular(float Red, float Green, float Blue)
{
	m_vSpecularReflect = glm::vec3(Red, Green, Blue);
}

void Material::setShininess(float shininess)
{
	m_fShininess = shininess;
}

glm::vec3 Material::getAmbient() 
{
	return m_vAmbientReflect;
}

glm::vec3 Material::getDiffuse() 
{
	return m_vDiffuseReflect;
}

glm::vec3 Material::getSpecular() 
{
	return m_vSpecularReflect;
}

float Material::getShininess()
{
	return m_fShininess;
}
