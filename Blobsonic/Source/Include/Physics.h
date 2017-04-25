#pragma once

#include "System.h"

namespace System {
	class Physics: public System {
	private:

		std::vector<std::shared_ptr <Entity>> m_vAABBS; // !< AABB for the scene
		std::vector<std::shared_ptr <Entity>> m_vOBBS; // !< OBB for the scene
		std::vector<std::shared_ptr <Entity>> m_vSpheres; // !< Spheres for the scene

		bool CheckAABBAABBCollision(std::shared_ptr <Entity> aabb1, std::shared_ptr <Entity> aabb2);
		bool CheckOBBOBBCollision(std::shared_ptr <Entity> obb1, std::shared_ptr <Entity> obb2);
		bool CheckShereSphereCollision(std::shared_ptr <Entity> sphere1, std::shared_ptr <Entity> sphere2);
		bool CheckOBBSphereCollision(std::shared_ptr <Entity> eBox, std::shared_ptr <Entity> eSphere);

		void updateOBB(std::shared_ptr <Entity> eBox);


	public:
		Physics();
		//! Process all entities
		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}