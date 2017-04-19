#pragma once

#include <stdafx.h>
#include "Entity.h"

class EntityManager {
private:

public:
	EntityManager();

	std::vector<std::shared_ptr<Entity>> m_entities;

	void addEntity(std::shared_ptr<Entity> newEntity);

	void update();
};