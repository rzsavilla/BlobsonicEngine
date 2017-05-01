#ifndef CAPSULE_H
#define CAPSULE_H

//Chris O'Neill


class Capsule : public Component::Component
{
public:
	Capsule(); // <! Default Constructor for a capsule pshyics physics

	glm::vec3 m_vSphereCenter1;
	glm::vec3 m_vSphereCenter2;
};



#endif // !BOXPHYSICS_H