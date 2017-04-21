#include "stdafx.h"
#include "CameraController.h"
#include "InputMessages.h"
#include "MessageHandler.h"

#include "Camera.h"

System::CameraController::CameraController()
{
	MessageHandler::getInstance()->attachReceiver(this);

	m_vMouseSensitivity = glm::vec2(1.0f, 1.0f);
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
	}
}

void System::CameraController::update(float dt)
{
	if (m_ActiveCamera != NULL) {
		//Get active camera component
		auto camera = m_ActiveCamera->get<Component::Camera>();

		//------Camera Mouse Rotation---------------------
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

		//Set previous mouse position;
		m_vPrevMousePos.x = m_vMousePos.x;
		m_vPrevMousePos.y = m_vMousePos.y;

		//std::cout << "Orientation: " << camera->getYaw() << " " << camera->getPitch() << " " << camera->getRoll() << std::endl;

		//------Camera movement -- key press-------------
		if (m_bAction[0]) {	//Zoom in
			camera->zoom(-camera->getMoveSpeed());
		}
		if (m_bAction[1]) {	//Zoom out
			camera->zoom(camera->getMoveSpeed());
		}
		if (m_bAction[2]) {	//Strafe left
			camera->strafe(-camera->getMoveSpeed());
		}
		if (m_bAction[3]) {	//Strafe right
			camera->strafe(camera->getMoveSpeed());
		}
		if (m_bAction[4]) {	//Roll left
			camera->roll(-camera->getMoveSpeed());
		}
		if (m_bAction[5]) {	//Roll right
			camera->roll(camera->getMoveSpeed());
		}
		if (m_bAction[6]) {	//Pedestal up
			camera->pedestal(camera->getMoveSpeed());
		}
		if (m_bAction[7]) {	//Pedestal down
			camera->pedestal(-camera->getMoveSpeed());
		}

		//Reset Camera Actions
		for (int i = 0; i < kiCameraActions; i++) {
			m_bAction[i] = false;
		}
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
				if (data->m_iAction == GLFW_PRESS || data->m_iAction == GLFW_REPEAT) {	//Key is pressed or held down
					if (data->m_iKey == GLFW_KEY_W) {
						m_bAction[0] = true;
					}
					else if (data->m_iKey == GLFW_KEY_S) {
						m_bAction[1] = true;
					}
					else if (data->m_iKey == GLFW_KEY_A) {
						m_bAction[2] = true;
					}
					else if (data->m_iKey == GLFW_KEY_D) {
						m_bAction[3] = true;
					}
					else if (data->m_iKey == GLFW_KEY_Q) {
						m_bAction[4] = true;
					}
					else if (data->m_iKey == GLFW_KEY_E) {
						m_bAction[5] = true;
					}
					else if (data->m_iKey == GLFW_KEY_Z) {
						m_bAction[6] = true;
					}
					else if (data->m_iKey == GLFW_KEY_X) {
						m_bAction[7] = true;
					}

					else if (data->m_iKey == GLFW_KEY_R) {
						camera->reset();
					}
				}
			}
		}
	}
}
