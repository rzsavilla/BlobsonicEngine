
#ifndef PHYSCIAL_H
#define PHYSCIAL_H


//Chris O'Neill



class Physical : public Component::Component
{
public:
	
	Physical(); // <! Default Contructor for physical Object

	float m_fMass; //<! Mass of object in kg's
	float m_fINVMass; //<! inverse mass Mass of object in kg's

	glm::vec3 m_fForce;	//<! Force of object in newtons
	glm::vec3 m_vVelocity; //<! Vel of object in m/s
	glm::vec3 m_vAcceleration; //<! Accel of object in m/s/s






};



#endif // !PHYSCIAL_H
