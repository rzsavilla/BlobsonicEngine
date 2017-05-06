#ifndef AABB_H
#define AABB_H

//Chris O'Neill


class AABB : public Component::Component
{
public:
	AABB(); // <! Default Constructor for a box/cube physics
public:

	//collision detection variables

	glm::vec3 obbLocalPoints[8];
	
	float m_fMinX; //!< min value on the x axis
	float m_fMinY; //!< min value on the y axis
	float m_fMinZ; //!< min value on the z axis
				  
	float m_fMaxX; //!< max value on the x axis
	float m_fMaxY; //!< max value on the y axis
	float m_fMaxZ; //!< max value on the z axis
	
	glm::vec3 m_vDimensions; // the distance from the center of the transformable to the edge (includes the scale )
	glm::vec3 m_vCenter;
	glm::vec3 m_vPosition;	//!< Camera World/Relative Position
	glm::vec3 m_vScale;		//!< Entity scale x,y,z
	glm::vec3 m_vRotation;	//!< x,y,z rotation in stored in degrees
	glm::vec3 m_vOrigin;	//!< x,y,z origin currently not applied

	glm::vec3 m_vLocalTransform;	//!< the position of the abb relative to the transform

	bool testAxis[3];
};



#endif // !BOXPHYSICS_H
