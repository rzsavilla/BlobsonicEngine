/**
*	@file Gameover.h
*	@class Gameover
*	@author Max Spencer-Hughes
*	@brief Gameover handler
*	System containing functions to detect and handle a gameover.
*/

#pragma once

#include "System.h"

namespace System
{
	class Gameover : public System
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_entities;

		/*!
		*	@brief Function Adds new entities to the vector of entities.
		*	Function compares UID of entity and stored entities if not found will add to the vector.
		*/
		void addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities);
		GLFWwindow *m_window;
		int width, height;
		bool m_bNoEnergy = false;
	public:
		Gameover();

		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
		void removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities);
	};
}