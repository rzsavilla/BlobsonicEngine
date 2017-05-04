#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::addEntity(std::shared_ptr<Entity> newEntity)
{
	m_entities.push_back(newEntity);
}

void EntityManager::destroy(std::shared_ptr<Entity> entity)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		//Find entity to destroy
		if ((*it)->getUID() == entity->getUID()) {
			(*it)->destroy();		//Call destroy to set entity as destroyed
			m_entities.erase(it);	//Remove entity from manager
			return;
		}
	}
}

void EntityManager::destroyAll()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		//Find entity to destroy
			(*it)->destroy();		//Set entity as destroyed
	}
	m_entities.clear();
}

void EntityManager::updateEntityManager()
{
	for (int i = 0; i < m_entities.size(); i++) {
		if (m_entities.at(i)->isDestroyed()) {
			m_entities.erase(m_entities.begin() + i);	//Remove Destroyed entity
		}
	}
}

std::shared_ptr<Entity> EntityManager::getEntityByName(std::string name)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		if ((*it)->getName() == name) {
			return (*it);		//Entity found
		}
	}
	return NULL;	//Entity not found
}

std::shared_ptr<Entity> EntityManager::getEntityByID(unsigned int ID)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		if ((*it)->getUID() == ID) {
			return (*it);		//Entity found
		}
	}
	return NULL;	//Entity not found
}
