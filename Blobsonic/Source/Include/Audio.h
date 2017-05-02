#pragma once

#include "System.h"
#include "Camera.h"

//Audio engine
#include <irrKlang\irrKlang.h>
using namespace irrklang;

namespace System {
	class Audio : public System {
	private:
		std::shared_ptr<Entity> m_ptrActiveCamera;

		std::vector<std::shared_ptr<Entity>> m_soundEntities;

	private:
		/*!
		*	@brief Function Adds new entities to the vector of entities.
		*	Function compares UID of entity and stored entities if not found will add to the vector.
		*/
		void addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities);

		//! Removed destroyed entities from vector
		void removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities);

		float m_fDeltaTime;

		ISoundEngine* engine;
	public:
		Audio();		//!< Default constructor
		~Audio();		//!< Default constructor

		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}