#include "stdafx.h"
#include "Audio.h"

//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

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

		if ((*it)->getID() == entity->getID()) {
			return;	//Entity already stored
		}
	}
	entities->push_back(entity);	//Store entity
}

void System::Audio::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			entities->erase(entities->begin() + i);
		}
	}
}

System::Audio::Audio()
{
	m_ptrActiveCamera = NULL;
	engine = createIrrKlangDevice();
	engine->play2D("Source/Resources/audio/getout.ogg", true);
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
		if ((*it)->has<Component::Camera>()) {
			auto cam = (*it)->get<Component::Camera>();
			//if (cam->m_bActive) {
			//Set camera pointer to this
			m_ptrActiveCamera = cam;
			//}
		}
	}
}

void System::Audio::update(float dt)
{

}

void System::Audio::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "SetActiveCamera") {
			//Get data key data from message
			auto data = static_cast<CameraMessage::SetActiveCamera*>((*it).get());

			m_ptrActiveCamera = data->entity->get<Component::Camera>();
		}
	}
}