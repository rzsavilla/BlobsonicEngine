#pragma once

#include <stdafx.h>
#include "Component.h"

class GameObject {
private:
	unsigned int m_uiHandle; //Object index
	std::vector<std::unique_ptr<Component>> m_ptrComponents;	//!< Stores all components object has.

	std::vector<Message*> m_vMessages;			//!< Messages passed to game objects for Components to read
	std::vector<Message*> m_vLocalMessages;		//!< Messages created by this objects components, will be read by other attached components

	void handleMessages() {
		//Iterate through components
		//std::cout << m_vMessages.size() << "\n";
		for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			//Send messages to components to handle
			for (int i = 0; i < m_vMessages.size(); i++) {
				//(*it)->handleMessage(m_vMessages.at(i));
			}
		}
		m_vMessages.clear();
		//Remove all messages
	}

	void handleLocalMessages() {
		//Iterate through components
		for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			//Send messages to components to handle
			for (int i = 0; i < m_vLocalMessages.size(); i++) {
				//(*it)->handleMessage(m_vLocalMessages.at(i));
			}
		}
		m_vLocalMessages.clear();		//Remove all local messages
	}

	void updateComponents(float dt) {
		//Iterate through components
		for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			(*it)->update(dt);
		}
	}
public:
	GameObject()	//!< Default constructor
	{

	}

	//! Used to add a message to the vector of messages from outside the object
	void sendMessage(Message* msg) {
		m_vMessages.push_back(msg);
	}

	//! Updates all attached components
	void update(float dt) {
		handleMessages();
		handleLocalMessages();

		updateComponents(dt);
	}

	//! Attaches a component to this object
	void attachComponent(std::unique_ptr<Component> newComponent) {
		m_ptrComponents.push_back(std::move(newComponent));
		//m_ptrComponents.back()->setLocalMsgPtr(&m_vLocalMessages);
	}
};