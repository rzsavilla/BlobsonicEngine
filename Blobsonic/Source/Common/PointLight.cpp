#include "stdafx.h"
#include "PointLight.h"

Component::PointLight::PointLight()
{
	
}

void Component::PointLight::setRadius(float radius)
{
	m_fRadius = radius;
}

float Component::PointLight::getRadius()
{
	return m_fRadius;
}
