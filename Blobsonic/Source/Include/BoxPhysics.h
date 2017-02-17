#ifndef BOXPHYSICS_H
#define BOXPHYSICS_H

#define GRAVITYCOEFFICENT -9.81 // m/s/s

//Chris O'Neill

#include "Model.h"
#include "Transformable.h"


class BoxPhysics : public Transformable , Component
{
public:
	BoxPhysics(); // <! Default Constructor for a box/cube physics
	BoxPhysics(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter

	Model m_RenderModel; // <! The rendered object

	void update(float dt);	//!< Update Box

	//Component Functions
	void init();							//!< Initialize component
	void handleMessage(std::shared_ptr<Message> msg);		//!< Each component will read and ignore Messages depending on implementation of this function														
	void setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr); // <!Allows component to access all local messages
	void CollideWithBox(BoxPhysics* other);			//<!Checks for collision with anotehr box


private:

	float m_fMass; //<! Mass of object in kg's
	glm::vec3 m_fForce;	//<! Force of object in newtons
	glm::vec3 m_fVelocity; //<! Vel of object in m/s
	glm::vec3 m_vAcceleration; //<! Accel of object in m/s/s

	glm::vec3 m_vCenter; //<! Center of cube used for collision
	glm::vec3 m_vExtends; //<! Half size of cube


	
};



#endif // !BOXPHYSICS_H
