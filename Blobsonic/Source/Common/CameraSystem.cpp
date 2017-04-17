#include <stdafx.h>
#include "CameraSystem.h"
#include "CameraMessages.h"
#include "InputMessages.h"
#include "RenderMessages.h"
#include "Transformable.h"

double dPrevMousePosX;
double dPrevMousePosY;
double dMousePosX;
double dMousePosY;

// Generate a quaternion from axis and rotation angle in radians
//This is to construct the rotation quaternion
glm::quat fromAxisAngle(glm::vec3 axis, float angle)
{
	glm::quat rotation;
	float r = (angle);

	rotation.w = cos(angle / 2);
	rotation.x = sin(angle / 2) * axis.x;
	rotation.y = sin(angle / 2) * axis.y;
	rotation.z = sin(angle / 2) * axis.z;
	return rotation;
}

void System::CameraSystem::updateView()
{
	//if (m_ptrActiveCamera != NULL) {
	//	//Update m_ptrActiveCamera
	//
	//	if (m_ptrActiveCamera->m_bFollowTarget) {
	//		m_ptrActiveCamera->m_view = glm::lookAt(m_ptrActiveCamera->m_vTarget + m_ptrActiveCamera->m_vCameraDist, m_ptrActiveCamera->m_vTarget, glm::vec3(0.0f, 1.0f, 0.0f));
	//	}
	//	else {
	//		m_ptrActiveCamera->m_view = glm::mat4_cast(m_ptrActiveCamera->m_qOrientation);
	//		//Coordinate axes from this matrix
	//		m_ptrActiveCamera->m_vAxisX = glm::vec3(m_ptrActiveCamera->m_view[0][0], m_ptrActiveCamera->m_view[1][0], m_ptrActiveCamera->m_view[2][0]);
	//		m_ptrActiveCamera->m_vAxisY = glm::vec3(m_ptrActiveCamera->m_view[0][1], m_ptrActiveCamera->m_view[1][1], m_ptrActiveCamera->m_view[2][1]);
	//		m_ptrActiveCamera->m_vAxisZ = glm::vec3(m_ptrActiveCamera->m_view[0][2], m_ptrActiveCamera->m_view[1][2], m_ptrActiveCamera->m_view[2][2]);
	//
	//		//Translate view matrix
	//		m_ptrActiveCamera->m_view[3][0] = -glm::dot(m_ptrActiveCamera->m_vAxisX, m_ptrActiveCamera->m_vPosition); //Translation x
	//		m_ptrActiveCamera->m_view[3][1] = -glm::dot(m_ptrActiveCamera->m_vAxisY, m_ptrActiveCamera->m_vPosition); //Translation y
	//		m_ptrActiveCamera->m_view[3][2] = -glm::dot(m_ptrActiveCamera->m_vAxisZ, m_ptrActiveCamera->m_vPosition); //Translation z
	//
	//		//MessageHandler::getInstance()->sendMessage(std::make_shared<RenderMessage::RenderCamera>(m_ptrActiveCamera));
	//	}
	//}
}

void System::CameraSystem::reset(void)
{
	//if (m_ptrActiveCamera != NULL) {
	//	//Initialise camera axes
	//	m_ptrActiveCamera->m_vAxisX = WORLDX;
	//	m_ptrActiveCamera->m_vAxisY = WORLDY;
	//	m_ptrActiveCamera->m_vAxisZ = WORLDZ;

	//	//Initialise camera position 
	//	m_ptrActiveCamera->m_vPosition = glm::vec3(0.0f, 0.0f, 5.0f);

	//	//Initialise the orientation
	//	m_ptrActiveCamera->m_qOrientation = glm::quat(1.0, 0.0, 0.0, 0.0);

	//	//Initialise camera perspective parameters
	//	m_ptrActiveCamera->m_fFieldOfView = glm::radians(50.0f);
	//	m_ptrActiveCamera->m_fNearPlane = 0.01f;
	//	m_ptrActiveCamera->m_fFarPlane = 1000.0f;
	//	m_ptrActiveCamera->m_fAspectRatio = 4.0f / 3.0f;

	//	m_ptrActiveCamera->m_projection = glm::perspective(m_ptrActiveCamera->m_fFieldOfView, m_ptrActiveCamera->m_fAspectRatio, m_ptrActiveCamera->m_fNearPlane, m_ptrActiveCamera->m_fFarPlane);
	//	//m_ptrActiveCamera->m_projection = glm::ortho(m_ptrActiveCamera->m_fFieldOfView, m_ptrActiveCamera->m_fAspectRatio, m_ptrActiveCamera->m_fNearPlane, m_ptrActiveCamera->m_fFarPlane);
	//}
}

System::CameraSystem::CameraSystem()
{
	MessageHandler::getInstance()->attachReceiver(this);	//Allow System to be notified of messages
	m_ptrActiveCamera = NULL;
}

void System::CameraSystem::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if ((*it)->has<Component::Camera>()) {
			m_ptrActiveCamera = (*it)->get<Component::Camera>();

			//if (m_ptrActiveCamera->m_bFollowTarget) {
			//	if ((*it)->has<Component::Transformable>()) {
			//		auto t = (*it)->get<Component::Transformable>();
			//		//mat4 look = glm::lookAt(m_ptrActiveCamera->m_vCameraDist, m_ptrActiveCamera->m_vTarget + m_ptrActiveCamera->m_vCameraDist, glm::vec3(0.0f, 1.0f, 0.0f));
			//		//m_ptrActiveCamera->m_view = look;
			//	}
			//}
		}
	}
}

void System::CameraSystem::update(float dt)
{
	//Rotate Camera based on mouse movement
	if (m_ptrActiveCamera != NULL) {
		glfwGetCursorPos(glfwGetCurrentContext(), &dMousePosX, &dMousePosY);
		double dX, dY;
		dX = dMousePosX - dPrevMousePosX;
		dY = dMousePosY - dPrevMousePosY;
		dX /= 25.0f;
		dY /= 25.0f;
		//rotate(glm::radians((float)dX), glm::radians((float)dY));
		//m_ptrActiveCamera->m_vCameraDist = glm::rotate(m_ptrActiveCamera->m_vCameraDist,glm::vec3(dX,dY,0.0f));
		dPrevMousePosX = dMousePosX;
		dPrevMousePosY = dMousePosY;
	}
	updateView();
	//std::cout << m_ptrActiveCamera->m_qOrientation.x << " " << m_ptrActiveCamera->m_qOrientation.y << " " << m_ptrActiveCamera->m_qOrientation.z << " \n";
	//m_ptrActiveCamera->m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
}

void System::CameraSystem::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (int i = 0; i < msgs->size(); i++) {
		std::string s = msgs->at(i)->sID;
		if (s == "Input_KeyPress") {
			if (m_ptrActiveCamera != NULL) {
				//Get data key data from message
				auto data = static_cast<InputMessage::KeyPress*>(msgs->at(i).get());
				if (data->m_iAction == GLFW_PRESS || data->m_iAction == GLFW_REPEAT) {	//Key is pressed
					if (data->m_iKey == GLFW_KEY_UP || data->m_iKey == GLFW_KEY_W) {
						//zoom(m_ptrActiveCamera->m_fMoveSpeed);
					}
					else if (data->m_iKey == GLFW_KEY_DOWN || data->m_iKey == GLFW_KEY_S) {
						//zoom(-m_ptrActiveCamera->m_fMoveSpeed);
					}
					else if (data->m_iKey == GLFW_KEY_LEFT || data->m_iKey == GLFW_KEY_A) {
						//pan(-m_ptrActiveCamera->m_fMoveSpeed, 0.0f);
						//m_ptrActiveCamera->m_qOrientation = glm::quat(glm::vec3(0.0f,0.0f,0.0f));

					}
					else if (data->m_iKey == GLFW_KEY_RIGHT || data->m_iKey == GLFW_KEY_D) {
						//pan(m_ptrActiveCamera->m_fMoveSpeed, 0.0f);
						//m_ptrActiveCamera->m_qOrientation.x +=0.1f;
					}
				}
			}
		}
	}
}

//void System::CameraSystem::setPosition(const glm::vec3 & position)
//{
//	if (m_ptrActiveCamera != NULL) m_ptrActiveCamera->m_vPosition = position;
//}
//
//void System::CameraSystem::setFieldOfView(float fieldOfView)
//{
//	assert(fieldOfView>0.0f && fieldOfView <180.0f);
//	if (m_ptrActiveCamera != NULL) m_ptrActiveCamera->m_fFieldOfView = fieldOfView;
//}
//
//void System::CameraSystem::setAspectRatio(float aspectRatio)
//{
//	assert(aspectRatio >0.0f);
//	if (m_ptrActiveCamera != NULL)m_ptrActiveCamera->m_fAspectRatio = aspectRatio;
//}
//
//void System::CameraSystem::setNearAndFarPlanes(float nearPlane, float farPlane)
//{
//	assert(nearPlane > 0.0f);
//	assert(farPlane > nearPlane);
//	if (m_ptrActiveCamera != NULL) m_ptrActiveCamera->m_fNearPlane = nearPlane;
//	if (m_ptrActiveCamera != NULL) m_ptrActiveCamera->m_fFarPlane = farPlane;
//}
//
//void System::CameraSystem::rotate(const float yaw, const float pitch)
//{
//	if (m_ptrActiveCamera != NULL) {
//		glm::quat xPitch = fromAxisAngle(WORLDX, pitch);
//		glm::quat yYaw = fromAxisAngle(WORLDY, yaw);
//		m_ptrActiveCamera->m_qOrientation = xPitch * m_ptrActiveCamera->m_qOrientation * yYaw;
//		if (m_ptrActiveCamera != NULL) m_ptrActiveCamera->m_qOrientation = glm::normalize(m_ptrActiveCamera->m_qOrientation);
//	}
//
//	//m_ptrActiveCamera->m_qOrientation = glm::rotate(m_ptrActiveCamera->m_qOrientation, 0.01f, glm::vec3(0.0f, 1.0, 0.0f));
//}
//
//void System::CameraSystem::pan(const float x, const float y)
//{
//	if (m_ptrActiveCamera != NULL) {
//		m_ptrActiveCamera->m_vPosition += m_ptrActiveCamera->m_vAxisX * x;
//		m_ptrActiveCamera->m_vPosition += m_ptrActiveCamera->m_vAxisY * -y;
//	}
//}
//
//void System::CameraSystem::roll(const float z)
//{
//	if (m_ptrActiveCamera != NULL) {
//		glm::quat zRoll = (fromAxisAngle(WORLDZ, z));
//		m_ptrActiveCamera->m_qOrientation = m_ptrActiveCamera->m_qOrientation * zRoll;
//		m_ptrActiveCamera->m_qOrientation = glm::normalize(m_ptrActiveCamera->m_qOrientation);
//	}
//}
//
//void System::CameraSystem::zoom(const float z)
//{
//	if (m_ptrActiveCamera != NULL) {
//		m_ptrActiveCamera->m_vPosition -= m_ptrActiveCamera->m_vAxisZ * z;
//	}
//}