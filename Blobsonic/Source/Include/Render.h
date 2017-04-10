#pragma once

#include "System.h"
#include "Camera.h"

namespace System {
	class Render : public System {
	private:
		Component::Camera* m_ptrActiveCamera;
	private:
		void renderModel(std::shared_ptr<Entity> entity);
	public:
		Render();

		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}