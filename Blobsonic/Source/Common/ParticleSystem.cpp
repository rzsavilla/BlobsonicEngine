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
			
			int numM = particle->getNumMax();
			particleMatrices = new glm::mat4[numM];
		}
		if ((*it)->has<Component::Camera>()) {
			m_ptrActiveCamera = (*it);
		}
	}
}

void System::ParticleSystem::update(float dt)
{
	for (auto it = 0; it != m_particleSystemEntity.size(); it++) {
		if (m_particleSystemEntity.at(it)->has<Component::Particle>()) {
			auto particle = m_particleSystemEntity.at(it)->get<Component::Particle>();
			for (GLuint i = 0; i < particle->getNumMax(); i++) {
				glm::mat4 pMat;
				glm::mat4* particleMatr = particle->getMatrix();
				glm::vec3 vel = particle->getVelocity();
				glm::vec3 pos = particle->getPosition();
				glm::vec3 interVel = vel*dt;
				pos += glm::vec3(1*i, 0, 1*i);
				pMat = glm::translate(pMat, pos);
				particleMatr[i] = pMat;
				particle->setMatrix(particleMatr);
			}
			particle->setBuffers();
		}

	}
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