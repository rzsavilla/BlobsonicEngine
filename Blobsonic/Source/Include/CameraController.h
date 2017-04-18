#pragma once

#include "System.h"

namespace System {
	const int kiCameraActions = 8;
	class CameraController: public System{
	private:
		std::shared_ptr<Entity> m_ActiveCamera;
		glm::dvec2 m_vMousePos;
		glm::dvec2 m_vPrevMousePos;
		glm::vec2 m_vMouseSensitivity;
		
		bool m_bAction[kiCameraActions];
	public:
		CameraController();

		void process(std::vector<std::shared_ptr<Entity>>* entities);
		void update(float dt);

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs);
	};
};