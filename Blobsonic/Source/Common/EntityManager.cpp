#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::addEntity(std::shared_ptr<Entity> newEntity)
{
	m_entities.push_back(newEntity);
}

void EntityManager::update()
{
	for (int i = 0; i < m_entities.size(); i++) {
		if (m_entities.at(i)->isDestroyed()) {
			m_entities.erase(m_entities.begin() + i);	//Remove Destroyed entity
		}
	}
}
