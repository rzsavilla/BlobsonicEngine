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
	


	
	
};



#endif // !BOXPHYSICS_H
