#include "stdafx.h"
#include "EntityFactory.h"
#include "Player.h"
#include "Movable.h"
#include "Model.h"
#include "Camera.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"
#include "Capsule.h"
#include "Physical.h"

EntityFactory::EntityFactory(ResourceManager * res)
{
	m_ptrResources = res;
}

std::shared_ptr<Entity> EntityFactory::create(std::string entity)
{
	if (entity == "Player") {
		return createPlayer(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity> EntityFactory::createPlayer(glm::vec3 position)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	//////Attach components
	entity->attach<Component::Transformable>();
	entity->attach<Component::Model>();
	entity->attach<Component::Player>();

	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	auto m = entity->get<Component::Model>();
	m->m_meshes.push_back(m_ptrResources->getMesh("cube"));
	m->m_textures.push_back(m_ptrResources->getTexture("red"));
	m->m_materials.push_back(m_ptrResources->getMaterial("default"));
	m->m_shader = m_ptrResources->getShader("phong");

	return entity;
}

std::shared_ptr<Entity> EntityFactory::createCamera(glm::vec3 position)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	//////Attach components
	entity->attach<Component::Transformable>();
	entity->attach<Component::Camera>();
	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	auto cam = entity->get<Component::Camera>();

	cam->setPosition(position);
	return entity;
}

std::shared_ptr<Entity> EntityFactory::createActor()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	//////Attach components
	entity->attach<Component::Transformable>();
	entity->attach<Component::Model>();
	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	return entity;
}


void EntityFactory::attachAABB(std::shared_ptr<Entity> entity, glm::vec3 position, glm::vec3 Dimensions, glm::vec3 Scale)
{
	//////Attach components
	if (!entity->has<Component::Transformable>()) {
		entity->attach<Component::Transformable>();
	}
	entity->attach<AABB>();
	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	auto a = entity->get<AABB>();

	//find the longest side of the whole object , so as the bounding box ebcases all orientation
	float fSize = std::max(Dimensions.x * Scale.x, Dimensions.y * Scale.y);
	fSize = std::max(fSize, Dimensions.z * Scale.z);

	t->m_vPosition = position;
	a->m_vDimensions = Dimensions;
	t->m_vScale = Scale;
	a->m_vCenter = position + (Dimensions * Scale) / 2.0f;

}

void EntityFactory::attachOBB(std::shared_ptr<Entity> entity, glm::vec3 position, glm::vec3 Dimensions, glm::vec3 Scale, glm::vec3 Rot)
{
	//////Attach components
  if (!entity->has<Component::Transformable>()) {
		entity->attach<Component::Transformable>();
	}
	entity->attach<OBB>();
	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	auto o = entity->get<OBB>();

	t->m_vPosition = position;
	o->m_vDimensions = Dimensions * Scale;
	t->m_vScale = Scale;

	o->m_Rotation = glm::rotate(o->m_Rotation, Rot.x, glm::vec3(1.0f, 0.0, 0.0f));
	o->m_Rotation = glm::rotate(o->m_Rotation, Rot.y, glm::vec3(0.0f, 1.0, 0.0f));
	o->m_Rotation = glm::rotate(o->m_Rotation, Rot.z, glm::vec3(0.0f, 0.0, 1.0f));

	o->m_vCenter = glm::mat3(o->m_Rotation) * (position + (Dimensions * Scale) / 2.0f);

	t->setRotation(Rot);
}

void EntityFactory::attachSphere(std::shared_ptr<Entity> entity, glm::vec3 position)
{
	//////Attach components
	if (!entity->has<Component::Transformable>()) {
		entity->attach<Component::Transformable>();
	}
	entity->attach<Sphere>();
	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	auto s = entity->get<Sphere>();

	t->m_vPosition = position;

	if (entity->has<AABB>()) 
	{
		auto AA = entity->get<AABB>();
		s->m_vCenter = AA->m_vCenter;
	}
	else if (entity->has<OBB>())
	{
		auto O = entity->get<OBB>();
		s->m_vCenter = O->m_vCenter;
	}
	else
	{
	
		s->m_vCenter = t->m_vPosition + (t->getScale() / 2.0f);
	}

	//find the largest scale of the sphere
	float fSize = std::max(t->m_vScale.x,  t->m_vScale.y);
	fSize = std::max(fSize, t->m_vScale.z);
	s->m_fRadius = fSize ;

	
}

void EntityFactory::attachCapsule(std::shared_ptr<Entity> entity, glm::vec3 position, glm::vec3 dimensions, glm::vec3 scale, glm::vec3 Rot)
{

	//////Attach components
	if (!entity->has<Component::Transformable>()) {
		entity->attach<Component::Transformable>();
	}

	if (!entity->has<OBB>()) {
		entity->attach<OBB>();
	}

	if (!entity->has<Sphere>()) {
		entity->attach<Sphere>();
	}

	if (!entity->has<Capsule>()) {
		entity->attach<Capsule>();
	}


	//Set OBB Properties
	auto t = entity->get<Component::Transformable>();
	auto o = entity->get<OBB>();

	t->m_vPosition = position;
	o->m_vDimensions = dimensions * scale;
	t->m_vScale = scale;

	o->m_Rotation = glm::rotate(o->m_Rotation, Rot.x, glm::vec3(1.0f, 0.0, 0.0f));
	o->m_Rotation = glm::rotate(o->m_Rotation, Rot.y, glm::vec3(0.0f, 1.0, 0.0f));
	o->m_Rotation = glm::rotate(o->m_Rotation, Rot.z, glm::vec3(0.0f, 0.0, 1.0f));

	o->m_vCenter = glm::mat3(o->m_Rotation) * (position + (dimensions * scale) / 2.0f);

	t->setRotation(Rot);


	//Set up sphere
	auto s = entity->get<Sphere>();

	float fSize = std::max(t->m_vScale.x, t->m_vScale.z);
	s->m_vCenter = t->m_vPosition;
	s->m_fRadius = fSize;

	//set up capsule
	auto c = entity->get<Capsule>();

	float x = o->m_vCenter.x;
	float y = o->m_vCenter.y + ((dimensions.y * scale.y) / 2.0f);
	float z = o->m_vCenter.z;

	c->m_vSphereCenter1 = glm::mat3(o->m_Rotation) * vec3(x,y,z);

	y = o->m_vCenter.y - ((dimensions.y * scale.y) / 2.0f);

	c->m_vSphereCenter2 = glm::mat3(o->m_Rotation) * vec3(x, y, z);
}

void EntityFactory::attachPhysical(std::shared_ptr<Entity> entity,float mass)
{
	if (!entity->has<Component::Transformable>()) {
		entity->attach<Component::Transformable>();
	}
	if (!entity->has<Physical>()) {
		entity->attach<Physical>();
	}
	auto physical = entity->get<Physical>();
	
	//apply the mass
	physical->m_fMass = mass;
	//check for infinite mass
	if (physical->m_fMass == 0)
	{
		physical->m_fINVMass = 0;
	}
	else
	{
		//set inverserse
		physical->m_fINVMass = 1 / mass;
	}



}