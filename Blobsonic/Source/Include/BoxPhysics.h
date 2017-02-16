#ifndef BOXPHYSICS_H
#define BOXPHYSICS_H

#include "Model.h"

class BoxPhysics
{
public:
	BoxPhysics(); // <! Default Constructor for a box/cube physics
	BoxPhysics(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter


	void draw();/*!< Draws the contents of this object */

private:
	Model m_RenderModel; // <! The rendered object


};



#endif // !BOXPHYSICS_H
