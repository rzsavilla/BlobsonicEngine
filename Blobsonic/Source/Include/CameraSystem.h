#pragma once

#define GLM_FORCE_RADIANS
#include <stdafx.h>
#include "System.h"
#include "Camera.h"

#include "MessageReceiver.h"
#include "MessageHandler.h"	//Allow system to send messages

#define PI 3.141592653589793
#define TWOPI 6.2831853071795862
#define TWOPI_F 6.2831853f
#define TO_RADIANS(x) (x * 0.017453292519943295)
#define TO_DEGREES(x) (x * 57.29577951308232)

//World coordinate System Axes
const glm::vec3 WORLDX = glm::vec3(1, 0, 0);
const glm::vec3 WORLDY = glm::vec3(0, 1, 0);
const glm::vec3 WORLDZ = glm::vec3(0, 0, 1);

namespace System {
	class CameraSystem : public System {
	private:
		Component::Camera* m_ptrActiveCamera;
	private:
		void setPosition(const glm::vec3& position); //position setter method
		void setFieldOfView(float fieldOfView); //fieldOfView setter method
		void setAspectRatio(float aspectRatio);  //aspectRatio setter method
		void setNearAndFarPlanes(float nearPlane, float farPlane); //nearPlane and farPLane setter method

		void rotate(const float yaw, const float pitch); //Rotate camera
		void pan(const float x, const float y);  //Pan camera
		void roll(const float z); //Roll camera
		void zoom(const float z); //Zoom camera

		void updateView();

		void reset(void); //Reset the camera
	public:
		CameraSystem();

		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}