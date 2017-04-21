#include "stdafx.h"
#include "EntityFactory.h"
#include "Player.h"
#include "Movable.h"
#include "Model.h"
#include "Camera.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"

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

void EntityFactory::attachSphere(std::shared_ptr<Entity> entity, glm::vec3 position, float radius)
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
	s->m_fRadius = radius;

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

	
}


