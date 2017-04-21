#pragma once

#include "stdafx.h"
#include "System.h"

namespace System {
	class PlayerController : public System {
	private:
		std::shared_ptr<Entity> m_vPlayer;	//Player entities
		static const int m_kiActions = 6;
		bool m_bAction[m_kiActions];
	public:
		PlayerController();

		void process(std::vector<std::shared_ptr<Entity>>* entities) ;
		void update(float dt);

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs);
	};
}