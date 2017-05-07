#include "stdafx.h"
#include "PlayerController.h"

#include "MessageHandler.h"
#include "InputMessages.h"

#include "Player.h"
#include "Transformable.h"
#include "Camera.h"
#include "Physical.h"

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
		if ((*it)->has<Component::Transformable>()) 
		{
			if ((*it)->getName() == "skybox")
			{
				m_vSkyBox = (*it);
			}
		}
		if ((*it)->has<Component::Camera>())
		{
			m_Camera = (*it);
		}
	}
}

void System::PlayerController::update(float dt) {
	if (m_vPlayer) {	//Check for null
		if (m_vPlayer->has<Component::Transformable>()) {
			//Player has a camera attached set camera to follow player
			auto player = m_vPlayer->get<Component::Player>();
			auto t = m_vPlayer->get<Component::Transformable>();
			if (m_vPlayer->has<Component::Camera>()) {
				auto cam = m_vPlayer->get<Component::Camera>();
				cam->setLookAtTarget(m_vPlayer);
				if (m_vSkyBox) {
					//Set skybox pos to follow player
					if (m_vSkyBox->has<Component::Transformable>()) {
						m_vSkyBox->get<Component::Transformable>()->setPosition(t->getPosition());
					}
				}

				//////Move player
				//if (m_vPlayer->has<Physical>()) {
				//	auto p = m_vPlayer->get<Physical>();
				//	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_T) > 0) {
				//		glm::vec4 vForward(0.0f, 0.0f, 1.0f, 0.0f);
				//		vForward = t->getTransform() * vForward;			//Rotate forward vector
				//		p->applyImpulse(glm::vec3(vForward), player->getMoveSpeed());
				//	}
				//}
			}
			
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
					m_bAction[0] = data->m_iAction;
					break;
				case GLFW_KEY_DOWN:
					m_bAction[1] = data->m_iAction;
					break;
				case GLFW_KEY_LEFT:
					m_bAction[2] = data->m_iAction;
					break;
				case GLFW_KEY_RIGHT:
					m_bAction[3] = data->m_iAction;
					break;
				case GLFW_KEY_J:
					m_bAction[4] = data->m_iAction;
					break;
				case GLFW_KEY_K:
					m_bAction[5] = data->m_iAction;
					break;
				default:
					break;
				}
			}
		}
	}
}

