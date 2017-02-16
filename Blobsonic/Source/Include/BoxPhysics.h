#ifndef BOXPHYSICS_H
#define BOXPHYSICS_H

#include "Model.h"

class BoxPhysics : 
{
public:
	BoxPhysics(); // <! Default Constructor for a box/cube physics
	BoxPhysics(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter

	Model m_RenderModel; // <! The rendered object

	void update(const float dt);	//!< Update Box

private:
	


};



#endif // !BOXPHYSICS_H
