#ifndef AABB_H
#define AABB_H

//Chris O'Neill

#include "Model.h"
#include "Physical.h"


class AABB : public Physical
{
public:
	AABB(); // <! Default Constructor for a box/cube physics
	AABB(Model model); // <! Overloaded Constructor for a box/cube physics , Takes the model as a parameter

	void update(float dt);	//!< Update Box

	//Component Functions
	void init();	//!< Initialize component
	void handleMessage(std::shared_ptr<Message> msg);		//!< Each component will read and ignore Messages depending on implementation of this function														
	void setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr); // <!Allows component to access all local messages
	void CollideWithBox(AABB* other);			//<!Checks for collision with anotehr box

	void movementForTesting(float x, float y, float z);
	Model m_RenderModel; // <! The rendered object for testing (Delete later)

private:

	//collision detection variables

	glm::vec3 obb1LocalPoints[8];
	glm::vec3 obb2LocalPoints[8];


	float m_fMinX; //!< min value on the x axis
	float m_fMinY; //!< min value on the y axis
	float m_fMinZ; //!< min value on the z axis
				  
	float m_fMaxX; //!< max value on the x axis
	float m_fMaxY; //!< max value on the y axis
	float m_fMaxZ; //!< max value on the z axis
	
	bool testAxis[3];

};



#endif // !BOXPHYSICS_H
