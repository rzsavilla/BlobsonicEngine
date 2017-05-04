#include "stdafx.h"
#include "ParticleSystem.h"

//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

#include "Particle.h"
#include "Transformable.h"


void System::ParticleSystem::addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {

		if ((*it)->getUID() == entity->getUID()) {
			return;	//Entity already stored
		}
	}
	entities->push_back(entity);	//Store entity
}

void System::ParticleSystem::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Remove entity from array
	int size = entities->size();
	if (!entities->empty()) {
		for (int i = entities->size() - 1; i > -1; i--) {
			if (entities->at(i)->isDestroyed()) {
				entities->erase(entities->begin() + i);
			}
		}
	}
}

System::ParticleSystem::ParticleSystem()
{
	m_ptrActiveCamera = NULL;
	
	MessageHandler::getInstance()->attachReceiver(this);
}

System::ParticleSystem::~ParticleSystem()
{
	
}

void System::ParticleSystem::process(std::vector<std::shared_ptr<Entity>>* entities)
{

	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		//Find and set active camera
		if ((*it)->has<Component::Particle>()) {
			auto particle = (*it)->get<Component::Particle>();
			addEntity((*it), &m_particleSystemEntity);
		}
		if ((*it)->has<Component::Camera>()) {
			m_ptrActiveCamera = (*it);
		}
	}
}

void System::ParticleSystem::update(float dt)
{

	removeDestroyed(&m_particleSystemEntity);
}

void System::ParticleSystem::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "Scene_Reload") {
			//engine->stopAllSounds();
		}
	}
}