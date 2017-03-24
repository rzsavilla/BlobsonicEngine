
#ifndef PHYSCIAL_H
#define PHYSCIAL_H

#define GRAVITYCOEFFICENT -9.81 // m/s/s

//Chris O'Neill


#include "Transformable.h"


class Physical : public Transformable, Component
{
public:
	

	void update(float dt);	//!< Update Box
							//Component Functions
	void init();							//!< Initialize component
	void handleMessage(std::shared_ptr<Message> msg);		//!< Each component will read and ignore Messages depending on implementation of this function														
	void setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr); // <!Allows component to access all local messages
	
	glm::vec3 getCenter();

protected:

	float m_fMass; //<! Mass of object in kg's
	glm::vec3 m_fForce;	//<! Force of object in newtons
	glm::vec3 m_fVelocity; //<! Vel of object in m/s
	glm::vec3 m_vAcceleration; //<! Accel of object in m/s/s
	glm::vec3 m_vCenter; //<! Center of cube used for collision


};



#endif // !PHYSCIAL_H
