#pragma once

#include "System.h"

namespace System {
	class Physics: public System {
	private:

	public:
		Physics();
		//! Process all entities
		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}