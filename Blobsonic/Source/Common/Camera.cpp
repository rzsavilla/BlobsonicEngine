#include "stdafx.h"
#include "Camera.h"

glm::mat4 Component::Camera::thirdPerson()
{
	if (m_LookAtTarget->has<Transformable>()) {
		auto t = m_LookAtTarget->get<Transformable>();
		glm::vec3 v = t->getPosition();	//Target position
		float fHorizontalDist = m_fReach * glm::cos(glm::radians(m_fPitch));
		float fVerticalDist = m_fReach * glm::sin(glm::radians(m_fPitch));
		float theta = t->getRotation().y;
		float fOffsetX = (float)fHorizontalDist * glm::sin(glm::radians(theta));
		float fOffsetZ = (float)fHorizontalDist * glm::cos(glm::radians(theta));
		float posx = t->getPosition().x - fOffsetX;
		float posy = t->getPosition().y + fVerticalDist;
		float posz = t->getPosition().z - fOffsetZ;

		m_fYaw = 180 - ((t->getRotation().y));
		return glm::lookAt(glm::vec3(posx, posy, posz), v, glm::vec3(0, 1, 0));
	}
}

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
	m_vUp = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	m_vLookAt = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

	m_bLocalPosSet = false;

	m_fReach = 1000.0f;

	m_bEnableRotate = true;
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
	setLocalPosition(newPosition);
	m_vPosition = newPosition;
}

void Component::Camera::setPosition(float x, float y, float z)
{
	setLocalPosition(glm::vec3(x,y,z));
	m_vPosition = glm::vec3(x, y, z);
}

void Component::Camera::setMoveSpeed(float speed)
{
	m_fMoveSpeed = speed;
}

void Component::Camera::setLocalPosition(glm::vec3 local)
{
	if (!m_bLocalPosSet) {
		m_vLocalPos = local;
		m_bLocalPosSet = true;
	}
}

void Component::Camera::setLookAtTarget(std::shared_ptr<Entity> entity)
{
	m_LookAtTarget = entity;
}

void Component::Camera::setReach(float reach)
{
	m_fReach = reach;
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
	if (m_fPitch < 0.0f) m_fPitch = 0.0f;
	else if (m_fPitch > 89.0f) m_fPitch = 89.0f;
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

glm::vec3 Component::Camera::getLocalPos()
{
	return m_vLocalPos;
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
	glm::vec4 intUp = glm::vec4(0, 1, 0, 0);
	glm::vec4 lookAt = glm::vec4(0, 0, 1,0);

	//Rotation Matrix
	glm::mat4 mRotation = glm::mat4_cast(getQuatRotation());
	
	m_vUp = mRotation*intUp;
	m_vLookAt = mRotation*lookAt;

	//Translation matrix
	glm::mat4 mTranslation = glm::mat4(1.0f);
	mTranslation = glm::translate(mTranslation, -m_vPosition);
	glm::vec3 v;
	if (m_LookAtTarget) {
		return thirdPerson();
	}
	
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
	glm::quat qOrientation = qPitch * qYaw;
	//qOrientation = qRoll * qOrientation;	//Roll disabled
	qOrientation = glm::normalize(qOrientation);

	return qOrientation;
}

glm::vec4 Component::Camera::getUp()
{
	return m_vUp;
}

glm::vec4 Component::Camera::getLookAt()
{
	return m_vLookAt;
}

void Component::Camera::enableRotation(bool enable)
{
	m_bEnableRotate = enable;
}

bool Component::Camera::isRotationEnabled()
{
	return m_bEnableRotate;
}

void Component::Camera::reset()
{
	m_vPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;
}
