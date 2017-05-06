#pragma once

#define GRAVITYCOEFFICENT -9.81 // m/s/s
#define EPSILON 0.5f
#define DRAG 0.75f

#include "System.h"

namespace System {
	class Physics : public System {
	private:
		/*!
		*	@brief Function Adds new entities to the vector of entities.
		*	Function compares UID of entity and stored entities if not found will add to the vector.
		*/
		void addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities);
		void removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities);

		std::vector<std::shared_ptr <Entity>> m_vAABBS; // !< AABB for the scene
		std::vector<std::shared_ptr <Entity>> m_vOBBS; // !< OBB for the scene
		std::vector<std::shared_ptr <Entity>> m_vSpheres; // !< Spheres for the scene
		std::vector<std::shared_ptr <Entity>> m_vCapsules; // !< Capsules for the scene
		std::vector<std::shared_ptr <Entity>> m_vPhysicals; // !< Physicals for the scene

		std::vector<std::shared_ptr <Entity>> m_vCheckSpheres; // !< Spheres for the scene
		std::vector<std::shared_ptr <Entity>> m_vCheckOBBS; // !< OBBs for the scene
		std::vector<std::shared_ptr <Entity>> m_vCheckCapsule; // !< Capsules for the scene

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
		void updateSphere(std::shared_ptr <Entity> eSphere);

		void resolveCollision(std::shared_ptr <Entity> object1, std::shared_ptr <Entity> object2, glm::vec3 CollisionNormal);
		void PositionalCorrection(std::shared_ptr <Entity> object1, std::shared_ptr <Entity> object2, float Depth, glm::vec3 CollisionNormal);

		void broadPhase(float dt);
		void narrowPhase(float dt);

		void applyImpulse(glm::vec3 Normal, float force, std::shared_ptr <Entity> object);

		/*!< 
			Stores entity ID's that we want to report upon a collision.
			If a collision with this entity ID occurs then a collision report is sent
		*/
		std::vector<int> m_vListenToCollision;	
	public:
		Physics();
		//! Process all entities
		void process(std::vector<std::shared_ptr<Entity>>* entities) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}