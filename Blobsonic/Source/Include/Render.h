#pragma once

#include "System.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Spotlight.h"

namespace System {
	class Render : public System {
	private:
		Component::Camera* m_ptrActiveCamera;

		std::vector<std::shared_ptr<Entity>> m_modelEntities;
		std::vector<std::shared_ptr<Entity>> m_textEntites;
		std::vector<std::shared_ptr<Entity>> m_directionalLights;	//!< Store all directional lights
		std::vector<std::shared_ptr<Entity>> m_pointLights;			//!< Store all point lights
		std::vector<std::shared_ptr<Entity>> m_spotlights;			//!< Store all spotlights
		std::vector<std::shared_ptr<Entity>> m_shadowmaps;			//!< Store all shadowmaps
	private:
		/*!
		*	@brief Function Adds new entities to the vector of entities.
		*	Function compares UID of entity and stored entities if not found will add to the vector.
		*/
		void addEntity(std::shared_ptr<Entity> entity , std::vector<std::shared_ptr<Entity>>* entities);

		void renderModel(std::shared_ptr<Entity> entity);
		void renderText(std::shared_ptr<Entity> entity);
		void renderSprite(std::shared_ptr<Entity> entity);
    
		void passLightUniforms(std::shared_ptr<GLSLProgram> shader);
		//! Removed destroyed entities from vector
		void removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities);
    
		float m_fDeltaTime;
	public:
		Render();		//!< Default constructor

		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}