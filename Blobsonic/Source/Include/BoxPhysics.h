#ifndef BOXPHYSICS_H
#define BOXPHYSICS_H

#define GRAVITYCOEFFICENT -9.81 // ms/s

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

	float m_fMass = 10; //<! Mass of object in kg's
	float m_fForce;	//<! Force of object in newtons


};



#endif // !BOXPHYSICS_H
