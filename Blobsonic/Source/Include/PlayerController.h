#pragma once

#include <stdafx.h>
#include "System.h"
#include "Player.h"

enum Action {
	forward,
	turnLeft,
	turnRight,
	backward,
};

namespace System {
	class PlayerController : public System {
	private:
		std::vector<std::shared_ptr<Entity>> m_vPlayers;	//Player entities
		bool m_bAction[4];
	public:
		PlayerController();

		void process(std::shared_ptr<Entity> entity);
		void update(float dt);

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs);
	};
}