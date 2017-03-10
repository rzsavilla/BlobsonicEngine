#pragma once

#include "Message.h"
#include "Camera.h"

namespace CameraMessage {
	struct SetActiveCamera : public Message {
		SetActiveCamera(Component::Camera* cam)
			:ptrCam(cam)
		{
			sID = "SetActiveCamera";
		}
		Component::Camera* ptrCam;
	};
}