/*
*	@file AIController.h
*	@class AIController
*	@brief System applies AI behaviour
*	@author Rozen Savilla
*	System takes control of entities with AI components and applies their behaviour
*/


#pragma once

#include "System.h"

namespace System {
	class AIController : public System {
	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;	//!< Entities with AI Components
	public:
		AIController();		//!< Default constructor

							//! Process all entities
		void process(std::vector<std::shared_ptr<Entity>>* entities);
		void update(float dt);

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs);
	};
};