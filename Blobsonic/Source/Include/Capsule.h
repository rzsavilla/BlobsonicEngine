#ifndef CAPSULE_H
#define CAPSULE_H

//Chris O'Neill


class Capsule : public Component::Component
{
public:
	Capsule(); // <! Default Constructor for a capsule pshyics physics

	glm::vec3 m_vSphereCenter1;
	glm::vec3 m_vSphereCenter2;

	//!Set the variables of a by reading the values set within a lua table
	void setComponent(luabridge::LuaRef& table) {};
};



#endif // !BOXPHYSICS_H