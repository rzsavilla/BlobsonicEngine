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

	bool testAxis[3];

};



#endif // !BOXPHYSICS_H
