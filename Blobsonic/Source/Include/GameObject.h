/**
* @class	GameObject
* @brief	Container for object components.
* @Author	Rozen Savilla
*/

#pragma once

#include <stdafx.h>
#include "ObjectComponent.h"

namespace OC {
	class GameObject {
	private:
		std::vector<std::unique_ptr<ObjectComponent>> m_vptrComponents;
		std::vector<std::shared_ptr<Message>> m_vptrLocalMessages;

		void handleMessages();
	public:
		//GameObject();	//!< Default constructor
		
		void sendMessage(Message* msg);	//<! Used to add a message to the vector of messages from outside the object
		void sendLocalMessage(std::shared_ptr<Message> msg);

		void update(float dt);

		void attachComponent(std::unique_ptr<ObjectComponent> component);
	};
}