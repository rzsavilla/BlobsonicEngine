#include "stdafx.h"
#include "Audio.h"

//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

#include "Sound.h"
#include "Transformable.h"

//Audio engine
#include <irrKlang\irrKlang.h>

// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <conio.h>
#endif

using namespace irrklang;

// To be able to use the irrKlang.dll file, we need to link with the irrKlang.lib.
// We could set this option in the project settings, but to make it easy we use
// a pragma comment:

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

void System::Audio::addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {

		if ((*it)->getUID() == entity->getUID()) {
			return;	//Entity already stored
		}
	}
	entities->push_back(entity);	//Store entity
}

void System::Audio::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Stop destroyed audio
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			auto s = entities->at(i)->get<Component::Sound>();
			irrklang::ISound* snd = s->getSound();
			snd->stop();
			snd->drop();
		}
	}

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

System::Audio::Audio()
{
	m_ptrActiveCamera = NULL;
	engine = createIrrKlangDevice();
	MessageHandler::getInstance()->attachReceiver(this);
}

System::Audio::~Audio()
{
	engine->drop(); // delete engine
}

void System::Audio::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		//Find and set active camera
		if ((*it)->has<Component::Sound>()) {
			auto sound = (*it)->get<Component::Sound>();
			addEntity((*it), &m_soundEntities);
		}
		if ((*it)->has<Component::Camera>()) {
			m_ptrActiveCamera = (*it);
		}
	}
}

void System::Audio::update(float dt)
{
	vec3 v;
	vec3df pos, doppler, up, lkat;
	glm::vec4 intUp, intlkat;

	for (auto it = m_soundEntities.begin(); it != m_soundEntities.end(); ++it) {
		//Find and set active camera
		if ((*it)->has<Component::Sound>()) {
			auto sound = (*it)->get<Component::Sound>();
			if (sound->getInitialized()) {
				if (!sound->getPlaying()) {
					sound->setInitialized(false);
					if (!sound->getsound3D())
						sound->startPlaying2D(engine);
					else if (sound->getsound3D()) {
						
						if ((*it)->has<Component::Transformable>()) {
							auto t = (*it)->get<Component::Transformable>();
							v = t->getPosition();
							pos.X = v.x;
							pos.Y = v.y;
							pos.Z = v.z;
							sound->setPos(pos);
						}
						sound->startPlaying3D(engine);
					}
				}
			}
			if (m_ptrActiveCamera != NULL) {
				if (m_ptrActiveCamera->has<Component::Transformable>()) {
					auto cam = m_ptrActiveCamera->get<Component::Camera>();
					v = cam->getPosition();
					pos.X = v.x;
					pos.Y = v.y;
					pos.Z = v.z;

								
					intUp = cam->getUp();
					intlkat = cam->getLookAt();

					up.X = intUp.x;
					up.Y = intUp.y;
					up.Z = intUp.z;

					lkat.X = intlkat.x;
					lkat.Y = intlkat.y;
					lkat.Z = intlkat.z;

					doppler = vec3df(0, 0, 0); //Default no doppler effect
					engine->setListenerPosition(pos, lkat, doppler, up);
				}
			}
			if (sound->getFinished() && !sound->getLooping()) {
				sound->stopPlaying(engine);
			}
		}
	}

	removeDestroyed(&m_soundEntities);
}

void System::Audio::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "Scene_Reload") {
			//engine->stopAllSounds();
		}
	}
}