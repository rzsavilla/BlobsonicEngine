#include "stdafx.h"
#include "PlayerController.h"

#include "MessageHandler.h"
#include "InputMessages.h"

#include "Player.h"
#include "Transformable.h"

System::PlayerController::PlayerController() {
	//Reset actions
	for (int i = 0; i < m_kiActions; i++) {
		m_bAction[i] = false;
	}

	MessageHandler::getInstance()->attachReceiver(this);
}

void System::PlayerController::process(std::vector<std::shared_ptr<Entity>>* entities) {
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if ((*it)->has<Component::Player>()) {
			m_vPlayer = (*it);
			return;
		}
	}
}

void System::PlayerController::update(float dt) {
	if (m_vPlayer) {
		if (m_vPlayer->has<Component::Transformable>()) {
			auto t = m_vPlayer->get<Component::Transformable>();
			auto p = m_vPlayer->get<Component::Player>();
			glm::vec3 pos = t->getPosition();
			float fSpeed = p->m_fMoveSpeed;
			if (m_bAction[0]) {		//Move Forward
				pos.z += fSpeed;
			}
			if (m_bAction[1]) {		//Move Backwards
				pos.z -= fSpeed;
			}
			if (m_bAction[2]) {		//Move Left
				pos.x -= fSpeed;
			}
			if (m_bAction[3]) {		//Move Right
				pos.x += fSpeed;
			}
			if (m_bAction[4]) {		//Move Up/Ascend
				pos.y += fSpeed;
			}
			if (m_bAction[5]) {		//Move Down/Descend
				pos.y -= fSpeed;
			}
			t->setPosition(pos);	//Set new position
		}
		for (int i = 0; i < m_kiActions; i++) {
			m_bAction[i] = false;
		}
	}
}

void System::PlayerController::processMessages(const std::vector<std::shared_ptr<Message>>* msgs) {
	//Read Input Messages
	for (int i = 0; i < msgs->size(); i++) {
		std::string s = msgs->at(i)->sID;

		if (s == "Input_KeyPress") {
			//Get data key data from message
			auto data = static_cast<InputMessage::KeyPress*>(msgs->at(i).get());
			if (data->m_iAction == GLFW_PRESS || data->m_iAction == GLFW_REPEAT) {	//Key is pressed
				switch (data->m_iKey)
				{
				case GLFW_KEY_UP:
					m_bAction[0] = true;
					break;
				case GLFW_KEY_DOWN:
					m_bAction[1] = true;
					break;
				case GLFW_KEY_LEFT:
					m_bAction[2] = true;
					break;
				case GLFW_KEY_RIGHT:
					m_bAction[3] = true;
					break;
				case GLFW_KEY_J:
					m_bAction[4] = true;
					break;
				case GLFW_KEY_K:
					m_bAction[5] = true;
					break;
				default:
					break;
				}
			}
		}
	}
}

