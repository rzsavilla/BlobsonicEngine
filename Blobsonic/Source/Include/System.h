/*
*	@class System
*	@brief Abstract class for systems
*/

#pragma once

#include "Entity.h"
#include "MessageHandler.h"

namespace System {
	class System : public MessageReceiver {
	private:
	public:
		//! Process all entities
		virtual void process(std::vector<std::shared_ptr<Entity>>* entities) = 0;
		virtual void update(float dt) = 0;

		//---Message Receiver--//
		virtual void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) = 0;
	};
}