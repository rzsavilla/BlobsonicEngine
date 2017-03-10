#ifndef SPHERE_H
#define SPHERE_H


//Chris O'Neill

#include "Model.h"
#include "Physical.h"


class Sphere : public Physical
{
public:
	Sphere(); // <! Default Constructor for a box/cube physics
	Sphere(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter

	void update(float dt);	//!< Update Box

							//Component Functions
	void init();	//!< Initialize component
	void handleMessage(std::shared_ptr<Message> msg);		//!< Each component will read and ignore Messages depending on implementation of this function														
	void setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr); // <!Allows component to access all local messages
	void CollideWithSphere(Sphere* other);			//<!Checks for collision with anotehr box

	void movementForTesting(float x, float y, float z);
	Model m_RenderModel; // <! The rendered object for testing (Delete later)

private:

	};



#endif // !BOXPHYSICS_H
