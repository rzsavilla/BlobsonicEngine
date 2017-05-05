#ifndef SPHERE_H
#define SPHERE_H


//Chris O'Neill


class Sphere : public Component::Component
{
public:
	Sphere(); // <! Default Constructor for a Sphere physics

	float m_fRadius; //<! The radius of the sphere (update when scaling the transformable)
	glm::vec3 m_vCenter; // <! Set manually , the position of the center of the cube (ideally set to the centre of the entity)

	glm::vec3 m_localCenter;	//!< Vector beetween transform and sphere center 

	glm::mat4 m_mRotation;
	glm::vec3 m_vRotation;	//!< x,y,z rotation in stored in degrees
	glm::vec3 m_vScale;		//!< Entity scale x,y,z


};


#endif // !SPHERE_H
