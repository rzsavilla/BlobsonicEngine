#include "stdafx.h"
#include "PlayerController.h"

#include "MessageHandler.h"
#include "InputMessages.h"

#include "Player.h"
#include "Transformable.h"
#include "Camera.h"

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
	if (m_Camera) {
		if (m_Camera->has<Component::Transformable>()) {
			auto t = m_Camera->get<Component::Camera>();
			auto p = m_Camera->get<Component::Player>();
			glm::vec3 pos = t->getPosition();
			float fSpeed = p->m_fMoveSpeed;

			//set the pos of skybox
			if (m_vSkyBox)
			{
				auto skytrans = m_vSkyBox->get<Component::Transformable>();

				skytrans->setPosition(t->getPosition());//- glm::vec3(250, 250, 250));
			}
		}
		for (int i = 0; i < m_kiActions; i++) {
			m_bAction[i] = false;
		}
	}

	if (m_vPlayer) {	//Check for null
		if (m_vPlayer->has<Component::Camera>()) {
			if (m_vPlayer->has<Component::Transformable>()) {
				auto cam = m_vPlayer->get<Component::Camera>();
				auto t = m_vPlayer->get<Component::Transformable>();
				cam->setPosition(t->getPosition() + cam->getLocalPos());
				std::cout << "cam: POs " << cam->getPosition().x << " " << cam->getPosition().y << " " << cam->getPosition().z << "\n";
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

