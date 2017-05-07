#include "stdafx.h"
#include "CameraController.h"
#include "InputMessages.h"
#include "MessageHandler.h"

#include "Camera.h"
#include "Transformable.h"
#include "Player.h"

System::CameraController::CameraController()
{
	MessageHandler::getInstance()->attachReceiver(this);

	m_vMouseSensitivity = glm::vec2(10.0f, 10.0f);
	m_vMousePos = glm::dvec2(0.0, 0.0);
	m_vPrevMousePos = glm::dvec2(0.0, 0.0);

	//Reset Camera Actions
	for (int i = 0; i < kiCameraActions; i++) {
		m_bAction[i] = false;
	}
}

void System::CameraController::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if ((*it)->has<Component::Camera>()) {
			m_ActiveCamera = (*it);		//Set Active camera
		}
		else if ((*it)->has<Component::Player>()) {
			m_ActiveCamera = (*it);		//Set Active camera
		}
	}
}

void System::CameraController::update(float dt)
{
	if (m_ActiveCamera != NULL) {
		//Get active camera component
		auto camera = m_ActiveCamera->get<Component::Camera>();

		//------Camera Mouse Rotation---------------------
		if (camera->isRotationEnabled()) {
			//Get current mouse position
			glfwGetCursorPos(glfwGetCurrentContext(), &m_vMousePos.x, &m_vMousePos.y);
			double dX, dY;	//Mouse move difference
			dX = m_vMousePos.x - m_vPrevMousePos.x;
			dY = m_vMousePos.y - m_vPrevMousePos.y;

			//Apply Mouse Sensitivity Settings
			dX *= m_vMouseSensitivity.x;
			dY *= m_vMouseSensitivity.y;

			//Apply rotation based on mouse movement
			camera->rotate(glm::radians((float)dY), glm::radians((float)dX));
			//Rotate player entity
			if (m_ActiveCamera->has<Component::Player>() && m_ActiveCamera->has<Component::Transformable>()) {
				auto t = m_ActiveCamera->get<Component::Transformable>();
				t->rotate(0.0f, glm::radians(dX * 0.1), 0.0f);
			}

			//Set previous mouse position;
			m_vPrevMousePos.x = m_vMousePos.x;
			m_vPrevMousePos.y = m_vMousePos.y;
		}

		//std::cout << "Orientation: " << camera->getYaw() << " " << camera->getPitch() << " " << camera->getRoll() << std::endl;

		GLFWwindow* window = glfwGetCurrentContext();
	}
}

void System::CameraController::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	//Create Input Messages
	for (int i = 0; i < msgs->size(); i++) {
		std::string s = msgs->at(i)->sID;

		if (s == "Input_KeyPress") {
			if (m_ActiveCamera) {
				auto camera = m_ActiveCamera->get<Component::Camera>();
				//Get data key data from message
				auto data = static_cast<InputMessage::KeyPress*>(msgs->at(i).get());
				if (true) {	//Key is pressed or held down
					if (data->m_iKey == GLFW_KEY_W) {
						m_bAction[0] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_S) {
						m_bAction[1] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_A) {
						m_bAction[2] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_D) {
						m_bAction[3] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_Q) {
						m_bAction[4] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_E) {
						m_bAction[5] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_Z) {
						m_bAction[6] = data->m_iAction;
					}
					else if (data->m_iKey == GLFW_KEY_X) {
						m_bAction[7] = data->m_iAction;
					}

					else if (data->m_iKey == GLFW_KEY_R) {
						//camera->reset();
					}
				}
			}
		}
	}
}
