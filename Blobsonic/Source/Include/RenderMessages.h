/*
Messages for the render system
*/

#pragma once

#include "Message.h"
#include "Camera.h"

namespace RenderMessage {
	struct RenderCamera : public Message {
		RenderCamera(Component::Camera* cam)
			:ptrCam(cam)
		{
			sID = "RenderCamera";
		}
		Component::Camera* ptrCam;
	};
}