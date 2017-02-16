#ifndef BOXPHYSICS_H
#define BOXPHYSICS_H

#define GRAVITYCOEFFICENT -9.81 // m/s/s

//Chris O'Neill

#include "Model.h"
#include "Transformable.h"


class BoxPhysics : public Transformable
{
public:
	BoxPhysics(); // <! Default Constructor for a box/cube physics
	BoxPhysics(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter

	Model m_RenderModel; // <! The rendered object

	void update(const float dt);	//!< Update Box

private:

	float m_fMass; //<! Mass of object in kg's
	glm::vec3 m_fForce;	//<! Force of object in newtons
	glm::vec3 m_fVelocity; //<! Vel of object in m/s
	glm::vec3 m_vAcceleration; //<! Accel of object in m/s/s

};



#endif // !BOXPHYSICS_H
