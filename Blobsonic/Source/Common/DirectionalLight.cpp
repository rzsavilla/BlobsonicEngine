#include "stdafx.h"
#include "DirectionalLight.h"

Component::DirectionalLight::DirectionalLight()
{
	m_vDirection = glm::vec3(0.0f);
}

void Component::DirectionalLight::setDirection(glm::vec3 dir)
{
	m_vDirection = dir;
}

glm::vec3 Component::DirectionalLight::getDirection()
{
	return m_vDirection;
}
