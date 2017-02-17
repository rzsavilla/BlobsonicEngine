/**
* @class	GameObject
* @brief	Container for object components.
* @Author	Rozen Savilla
*/

#pragma once

#include <stdafx.h>
#include "ObjectComponent.h"

namespace OC {
	class GameObject : public ObjectComponent {
	private:

	public:
		GameObject();	//!< Default constructor
		
		void sendMessage(Message* msg);	//<! Used to add a message to the vector of messages from outside the object

		void handleGlobalMessages();

		void handleLocalMessages();

		void update(float dt);
	};
}