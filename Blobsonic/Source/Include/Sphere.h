#ifndef SPHERE_H
#define SPHERE_H


//Chris O'Neill


class Sphere : public Component::Component
{
public:
	Sphere(); // <! Default Constructor for a Sphere physics

	float m_fRadius; //<! The radius of the sphere (update when scaling the transformable)
	glm::vec3 m_vCenter; // <! Set manually , the position of the center of the cube (ideally set to the centre of the entity)
	glm::mat4 m_Rotation;
};


#endif // !SPHERE_H
