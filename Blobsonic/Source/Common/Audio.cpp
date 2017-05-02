#include "stdafx.h"
#include "Audio.h"

//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

#include "Sound.h"

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
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			auto s = entities->at(i)->get<Component::Sound>();
			irrklang::ISound* snd = s->getSound();
			snd->stop();
			snd->drop();
			entities->erase(entities->begin() + i);
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
	}
}

void System::Audio::update(float dt)
{
	for (auto it = m_soundEntities.begin(); it != m_soundEntities.end(); ++it) {
		//Find and set active camera
		if ((*it)->has<Component::Sound>()) {
			auto sound = (*it)->get<Component::Sound>();
			if (sound->getInitialized()) {
				if (!sound->getPlaying()) {
					sound->setInitialized(false);
					sound->startPlaying(engine);
					
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
		if ((*it)->sID == "SetActiveCamera") {
			//Get data key data from message
			auto data = static_cast<CameraMessage::SetActiveCamera*>((*it).get());
			m_ptrActiveCamera = data->entity->get<Component::Camera>();
		}
		if ((*it)->sID == "Scene_Reload") {
			//engine->stopAllSounds();
		}
	}
}