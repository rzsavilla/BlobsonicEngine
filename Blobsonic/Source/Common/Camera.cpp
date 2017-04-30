#include "stdafx.h"
#include "Camera.h"

Component::Camera::Camera()
{
	m_bUsePerspective = true;		//Default perspective view

	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;

	m_fFieldOfView = glm::radians(45.0f);
	m_fNearPlane = 0.01f;
	m_fFarPlane = 1000.0f;
	m_fAspectRatio = 4.0f / 3.0f;;

	m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 5.0f;
};

void Component::Camera::setProjectionAtt(float FOV, float AspectRatio, float Near, float Far)
{
	setFOV(FOV);
	setAspectRatio(AspectRatio);
	setNearPlane(Near);
	setFarPlane(Far);
}

void Component::Camera::setFOV(float FOV)
{
	if (FOV < 0) FOV = 0;
	else if (FOV > 180) FOV = 180;
	m_fFieldOfView = glm::radians(FOV);
}

void Component::Camera::setAspectRatio(float AspectRatio)
{
	m_fAspectRatio = AspectRatio;
}

void Component::Camera::setNearPlane(float Near)
{
	m_fNearPlane = Near;	
}

void Component::Camera::setFarPlane(float Far)
{
	m_fFarPlane = Far;
}

void Component::Camera::setOrientation(glm::vec3 newOrientation)
{
	setYaw(newOrientation.x);
	setPitch(newOrientation.y);
	setRoll(newOrientation.z);
}

void Component::Camera::setOrientation(float pitch, float yaw, float roll)
{
	setPitch(pitch);
	setYaw(yaw);
	setRoll(roll);
}

void Component::Camera::setPitch(float pitch)
{
	m_fPitch = glm::radians(pitch);
}

void Component::Camera::setYaw(float yaw)
{
	m_fYaw = glm::radians(yaw);
}

void Component::Camera::setRoll(float roll)
{
	m_fRoll = glm::radians(roll);
}

void Component::Camera::setPosition(glm::vec3 newPosition)
{
	m_vPosition = newPosition;
}

void Component::Camera::setPosition(float x, float y, float z)
{
	m_vPosition = glm::vec3(x, y, z);
}

void Component::Camera::setMoveSpeed(float speed)
{
	m_fMoveSpeed = speed;
}

void Component::Camera::zoom(float zoom)
{
	//Forward vector
	glm::vec3 vForward = glm::vec3(0.0f, 0.0f, zoom);
	vForward = vForward * getQuatRotation() ;			//Rotate forward vector

	m_vPosition += vForward;	//Translate based on orientation
}

void Component::Camera::strafe(float strafe)
{
	//Forward vector
	glm::vec3 vForward = glm::vec3(strafe, 0.0f, 0.0f);
	vForward = vForward* getQuatRotation();			//Rotate forward vector

	m_vPosition += vForward;	//Translate based on orientation
}

void Component::Camera::pedestal(float pedestal)
{
	//Forward vector
	glm::vec3 vForward = glm::vec3(0.0f, pedestal, 0.0f);
	vForward = vForward* getQuatRotation();			//Rotate forward vector

	m_vPosition += vForward;	//Translate based on orientation
}

void Component::Camera::pitch(float pitch)
{
	m_fPitch += glm::radians(pitch);
}

void Component::Camera::yaw(float yaw)
{
	m_fYaw += glm::radians(yaw);
}

void Component::Camera::roll(float roll)
{
	m_fRoll += glm::radians(roll);
}

void Component::Camera::translate(glm::vec3 position)
{
	m_vPosition += position;
}

void Component::Camera::translate(float x, float y, float z)
{
	m_vPosition += glm::vec3(x, y, z);
}

void Component::Camera::rotate(float pitch, float yaw)
{
	this->pitch(pitch);	//Apply pitch
	this->yaw(yaw);		//apply yaw
}

float Component::Camera::getPitch()
{
	return glm::degrees(m_fPitch);
}

float Component::Camera::getYaw()
{
	return glm::degrees(m_fYaw);
}

float Component::Camera::getRoll()
{
	return glm::degrees(m_fRoll);
}

glm::vec3 Component::Camera::getPosition()
{
	return m_vPosition;
}

float Component::Camera::getMoveSpeed()
{
	return m_fMoveSpeed;
}

void Component::Camera::setPerspective(bool isPerspective)
{
	m_bUsePerspective = isPerspective;
}

glm::mat4 Component::Camera::getView()
{
	//Rotation Matrix
	glm::mat4 mRotation = glm::mat4_cast(getQuatRotation());

	//Translation matrix
	glm::mat4 mTranslation = glm::mat4(1.0f);
	mTranslation = glm::translate(mTranslation, -m_vPosition);

	return mRotation * mTranslation;	//Return view matrix
}

glm::mat4 Component::Camera::getProjection()
{
	if (m_fNearPlane <= 0) m_fNearPlane = 0.1f;
	if (m_fFarPlane <= m_fNearPlane) m_fFarPlane = 1000.0f;

	if (m_bUsePerspective) {
		//Perspective projection
		return glm::perspective(m_fFieldOfView, m_fAspectRatio, m_fNearPlane, m_fFarPlane);
	}
	else {
		//Orthographic projection	//Currently broken
		glm::ivec2 windowSize;
		glfwGetWindowSize(glfwGetCurrentContext(), &windowSize.x, &windowSize.y);
		//return glm::ortho(0.0f, (float)windowSize.x, 0.0f, (float)windowSize.y, m_fNearPlane, m_fFarPlane);
		//return glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, 0.1f, 1000.0f);
		//return glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
		return glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, 0.1f, 100.0f);
	}
}

glm::quat Component::Camera::getQuatRotation()
{
	//Get quaternion rotations for x,y,z axis
	glm::quat qPitch = glm::angleAxis(m_fPitch, glm::vec3(1.0f, 0.0f, 0.0f));	//Rotation around X axis
	glm::quat qYaw = glm::angleAxis(m_fYaw, glm::vec3(0.0f, 1.0f, 0.0f));		//Rotation around Y axis
	glm::quat qRoll = glm::angleAxis(m_fRoll, glm::vec3(0.0f, 0.0f, 1.0f));		//Rotation around Z axis

	//Rotation matrix
	glm::quat qOrientation = qPitch * qYaw * qRoll;
	qOrientation = glm::normalize(qOrientation);

	return qOrientation;
}

void Component::Camera::reset()
{
	m_vPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;

}
