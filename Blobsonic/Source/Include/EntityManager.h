#pragma once

#include <stdafx.h>
#include "Entity.h"

class EntityManager {
private:

public:
	EntityManager() {}

	std::vector<std::shared_ptr<Entity>> m_entities;

	void addEntity(std::shared_ptr<Entity> newEntity);
	//{
	//	m_entities.push_back(newEntity);
	//}

	void update();
	//	{
	//	for (auto it = m_entities.begin(); it != m_entities.end(); ++it);
	//	{
	//		//Look for destroyed entites
	//		if ((*it)->isDestroyed()) {
	//			m_entities.erase(it);		//Remove destroyed entites from vector
	//		}
	//	}
	//}
};