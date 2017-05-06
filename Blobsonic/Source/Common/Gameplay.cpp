#include "stdafx.h"
#include "Gameplay.h"
#include "Player.h"
#include "Pickup.h"

System::Gameplay::Gameplay()
{
	MessageHandler::getInstance()->attachReceiver(this);
}

void System::Gameplay::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		//Sort all entities;
		if ((*it)->has<Component::Player>()) {
			m_Player = (*it);
		}
		else if ((*it)->has<Component::Pickup>()) {
			m_Pickups.push_back((*it));
		}
	}
}

void System::Gameplay::update(float dt)
{
	/*
		Gameplay updates here
	*/

	if (m_Player) {
		//Player collision with pickups
		if (m_Player->getUID()) {
			for (auto it = m_Player->m_vCollidedWith.begin(); it != m_Player->m_vCollidedWith.end(); ++it) {

			}
		}
	}

	m_Pickups.clear();
}

void System::Gameplay::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{

}