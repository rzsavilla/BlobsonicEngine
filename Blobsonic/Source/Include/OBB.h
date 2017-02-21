#ifndef OBB_H
#define OBB_H

#define GRAVITYCOEFFICENT -9.81 // m/s/s

//Chris O'Neill

#include "Model.h"
#include "Physical.h"


class OBB : public Physical , Component
{
public:
	OBB(); // <! Default Constructor for a box/cube physics
	OBB(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter

	Model m_RenderModel; // <! The rendered object

	void update(float dt);	//!< Update Box

	//Component Functions
	void init();							//!< Initialize component
	void handleMessage(std::shared_ptr<Message> msg);		//!< Each component will read and ignore Messages depending on implementation of this function														
	void setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr); // <!Allows component to access all local messages
	void CollideWithBox(OBB* other);			//<!Checks for collision with anotehr box

	void movementForTesting(float x, float y, float z);


private:

	//Collision detection variables
	glm::vec3 obb1LocalPoints[8];
	glm::vec3 obb2LocalPoints[8];
	glm::vec3 obb1Normals[6];
	glm::vec3 obb2Normals[6];
	glm::vec3 separetedAxis[6];
	bool testAxis[6];
	

	
};



#endif // !BOXPHYSICS_H
