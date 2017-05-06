/*
*	@file Gameplay.h
*	@class Gameplay
*	@brief Gameplay implements gameplay mechanics
*	@author Rozen Savilla
*/


#pragma once

#include "System.h"

namespace System {
	class Gameplay : public System {
	private:
		std::shared_ptr<Entity> m_Player;
		std::vector<std::shared_ptr<Entity>> m_Pickups;
	public:
		Gameplay();

		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}