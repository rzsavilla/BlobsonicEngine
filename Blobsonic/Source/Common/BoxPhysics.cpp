#include <stdafx.h>
#include "BoxPhysics.h"

BoxPhysics::BoxPhysics()
{
	m_vPosition = glm::vec3(1.0f,20.0f,1.0f)


}

BoxPhysics::BoxPhysics(Model model)
{
	m_RenderModel = model;
}

void BoxPhysics::update(const float dt)
{



	//F = M * A 
	m_fForce = m_fMass * GRAVITYCOEFFICENT;

	//suvat foor fal





}

