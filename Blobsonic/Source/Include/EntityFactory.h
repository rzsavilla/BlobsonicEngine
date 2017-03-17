#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

class EntityFactory {
private:
	ResourceManager* m_ptrResources;
public:
	EntityFactory(ResourceManager* res);

	std::shared_ptr<Entity> create(std::string entity);

	std::shared_ptr<Entity> createPlayer(glm::vec3 position);	//Entity with transformable,movable,player and model components

	std::shared_ptr<Entity> createCamera(glm::vec3 position);
};