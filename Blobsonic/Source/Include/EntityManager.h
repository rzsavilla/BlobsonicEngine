#pragma once

#include <stdafx.h>
#include "Entity.h"

class EntityManager {
public:
	EntityManager();

	std::vector<std::shared_ptr<Entity>> m_entities;	//!< Stores all entities

	void addEntity(std::shared_ptr<Entity> newEntity);	//!< Adds entity to vector of entities

	void destroy(std::shared_ptr<Entity> entity);	//!< Destroy this entity

	void destroyAll();	//!< Destroy all entities stored in the manager;

	void updateEntityManager();	//!< Updates entities removing all destroyed entities from its vector
};