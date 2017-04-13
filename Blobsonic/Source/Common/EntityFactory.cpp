#include "stdafx.h"
#include "EntityFactory.h"
#include "Player.h"
#include "Movable.h"
#include "Model.h"
#include "Camera.h"
#include "AABB.h"

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

	cam->m_vPosition = position;
	cam->m_bActive = true;
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
	entity->attach<Component::Transformable>();
	entity->attach<AABB>();
	//Set component Properties
	auto t = entity->get<Component::Transformable>();
	auto a = entity->get<AABB>();
	

	//find the longest side of the whole object , so as the bounding box ebcases all orientation
	float fSize = std::max(Dimensions.x * Scale.x, Dimensions.y * Scale.y);
	fSize = std::max(fSize, Dimensions.z * Scale.z);
	a->m_vDimensions = glm::vec3(fSize, fSize, fSize);

	t->setPosition(position);
	t->m_vDimensions = Dimensions;
	t->m_vScale = Scale;
	t->m_vCenter = position + Dimensions * Scale / 2.0f;

}
