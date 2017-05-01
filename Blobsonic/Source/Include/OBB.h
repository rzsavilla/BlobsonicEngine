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

	glm::vec3 m_vDimensions;	//Plz move to different component
	glm::vec3 m_vCenter;

	//!Set the variables of a by reading the values set within a lua table
	void setComponent(luabridge::LuaRef& table) {};
};



#endif // !BOXPHYSICS_H
