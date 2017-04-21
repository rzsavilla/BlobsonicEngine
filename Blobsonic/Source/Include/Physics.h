#pragma once

#include "System.h"

namespace System {
	class Physics: public System {
	private:

		std::vector<std::shared_ptr <Entity>> m_vAABBS; // !< AABB for the scene
		std::vector<std::shared_ptr <Entity>> m_vOBBS; // !< OBB for the scene

		bool CheckAABBAABBCollision(std::shared_ptr <Entity> aabb1, std::shared_ptr <Entity> aabb2);
		bool CheckOBBOBBCollision(std::shared_ptr <Entity> obb1, std::shared_ptr <Entity> obb2);


	public:
		Physics();
		//! Process all entities
		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}