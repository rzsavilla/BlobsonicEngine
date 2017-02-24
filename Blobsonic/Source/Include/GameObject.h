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
		std::vector<std::shared_ptr<Message>> m_vptrMessages;

		void handleMessages(std::shared_ptr<Message> msg);
	public:
		GameObject();	//!< Default constructor
		
		void sendMessage(Message* msg);	//<! Used to add a message to the vector of messages from outside the object

		void update(float dt);

		void attachComponent(std::unique_ptr<ObjectComponent> component);
	};
}