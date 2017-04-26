#pragma once

#define GRAVITYCOEFFICENT -9.81 // m/s/s

#include "System.h"

namespace System {
	class Physics : public System {
	private:

		std::vector<std::shared_ptr <Entity>> m_vAABBS; // !< AABB for the scene
		std::vector<std::shared_ptr <Entity>> m_vOBBS; // !< OBB for the scene
		std::vector<std::shared_ptr <Entity>> m_vSpheres; // !< Spheres for the scene
		std::vector<std::shared_ptr <Entity>> m_vCapsules; // !< Capsules for the scene
		std::vector<std::shared_ptr <Entity>> m_vPhysicals; // !< Physicals for the scene

		bool CheckAABBAABBCollision(std::shared_ptr <Entity> aabb1, std::shared_ptr <Entity> aabb2);
		bool CheckOBBOBBCollision(std::shared_ptr <Entity> obb1, std::shared_ptr <Entity> obb2);
		bool CheckShereSphereCollision(std::shared_ptr <Entity> sphere1, std::shared_ptr <Entity> sphere2);
		bool CheckOBBSphereCollision(std::shared_ptr <Entity> eBox, std::shared_ptr <Entity> eSphere);

		bool CheckOBBCapsuleCollision(std::shared_ptr <Entity> eCap, std::shared_ptr <Entity> eBox);
		bool CheckSphereCapsuleCollision(std::shared_ptr <Entity> eCap, std::shared_ptr <Entity> eSphere);
		bool CheckCapsuleCapsuleCollision(std::shared_ptr <Entity> eCap1, std::shared_ptr <Entity> eCap2);

		void updateOBB(std::shared_ptr <Entity> eBox);
		void updateAABB(std::shared_ptr <Entity> eBox);

		void updatePhysicals(std::shared_ptr <Entity> e, float dt);


	public:
		Physics();
		//! Process all entities
		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}