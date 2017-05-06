#ifndef OBB_H
#define OBB_H

//Chris O'Neill



class OBB : public Component::Component
{
public:
	OBB(); // <! Default Constructor for a box/cube physics

	//Collision detection variables
	glm::vec3 m_obbLocalPoints[8];
	glm::vec3 m_obbNormals[6];
	glm::mat4 m_Rotation;

	glm::vec3 m_vCenter;

	glm::vec3 m_vPosition;	//!< Camera World/Relative Position
	glm::vec3 m_vScale;		//!< Entity scale x,y,z
	glm::vec3 m_vRotation;	//!< x,y,z rotation in stored in degrees
	glm::vec3 m_vOrigin;	//!< x,y,z origin currently not applied
	
	glm::vec3 m_vLocalPos;	//!< Vector diff between this and transformable
};



#endif // !BOXPHYSICS_H
