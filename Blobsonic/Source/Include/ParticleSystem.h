#pragma once

#include "System.h"
#include "Camera.h"

namespace System {
	class ParticleSystem : public System {
	private:
		std::shared_ptr<Entity> m_ptrActiveCamera;

		std::vector<std::shared_ptr<Entity>> m_particleSystemEntity;

		glm::mat4* particleMatrices;

	private:
		/*!
		*	@brief Function Adds new entities to the vector of entities.
		*	Function compares UID of entity and stored entities if not found will add to the vector.
		*/
		void addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities);

		//! Removed destroyed entities from vector
		void removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities);

		float m_fDeltaTime;

	public:
		ParticleSystem();		//!< Default constructor
		~ParticleSystem();		//!< Default constructor

		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}