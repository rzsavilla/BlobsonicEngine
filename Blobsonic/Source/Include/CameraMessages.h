#pragma once

#include "Message.h"
#include "Camera.h"

namespace CameraMessage {
	struct SetActiveCamera : public Message {
		SetActiveCamera(std::shared_ptr<Entity> CameraEntity)
			:entity(CameraEntity)
		{
			sID = "SetActiveCamera";
		}
		std::shared_ptr<Entity> entity;
	};
}