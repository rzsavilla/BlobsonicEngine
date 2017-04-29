#include "stdafx.h"
#include "Spotlight.h"

Component::Spotlight::Spotlight()
{
}

void Component::Spotlight::setDirection(glm::vec3 direction)
{
	m_vDirection = direction;
}

void Component::Spotlight::setCutOff(float cutOff)
{
	m_fCutOff = glm::radians(cutOff);
}

void Component::Spotlight::setOuterCutOff(float outerCutOff)
{
	m_fOuterCutoff = glm::radians(outerCutOff);
}

void Component::Spotlight::setConstant(float constant)
{
	m_fConstant = constant;
}

void Component::Spotlight::setLinear(float linear)
{
	m_fLinear = linear;
}

void Component::Spotlight::setQuadratic(float quadratic)
{
	m_fQuadratic = quadratic;
}

glm::vec3 Component::Spotlight::getDirection()
{
	return m_vDirection;
}

float Component::Spotlight::getCutOff()
{
	return m_fCutOff;
}

float Component::Spotlight::getOuterCutOff()
{
	return m_fOuterCutoff;
}

float Component::Spotlight::getConstant()
{
	return m_fConstant;
}

float Component::Spotlight::getLinear()
{
	return m_fLinear;
}

float Component::Spotlight::getQuadratic()
{
	return m_fQuadratic;
}
