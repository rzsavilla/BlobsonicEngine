#include "stdafx.h"
#include "EntityManager.h"

void EntityManager::addEntity(std::shared_ptr<Entity> newEntity)
{
	m_entities.push_back(newEntity);
}

void EntityManager::update()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		//Look for destroyed entites
		if ((*it)->isDestroyed()) {
			m_entities.erase(it);		//Remove destroyed entites from vector
		}
	}
}
