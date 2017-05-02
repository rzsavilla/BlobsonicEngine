/*
*	@class LuaScripting
*	@brief System handles lua scripts.
*	@author Rozen Savilla
*	Handles loading and using lua scripts acts as an interface to lua to call C++ functions/class
*/

#pragma once

#include "System.h"
#include <iostream>

#include "LuaHelper.h"

#include "SceneManager.h"

static void sayHello() {
	std::cout << "\n\n HELLO WORLD \n\n";
}

namespace System {
	namespace Scripting {
		static bool isKeyDown(const std::string& key);		//!< Check if a key is pressed
		static bool isMouseDown(const std::string& button);	//!< Check if a mouse button is down
		static void changeScene(std::string sceneFile);			//!< Change to scene
		static void setLoadingScene(std::string sceneFile);		//!< Set loading scene
		static void reloadScene();		//!< Set loading scene
		static void forceReloadScene();		//!< Set loading scene

		class LuaScripting : public System {
		private:
			std::shared_ptr<SceneManager> m_SceneManager;

			const bool m_bDebug = true;	//For couts
			const std::string m_scriptsDir = "Source/Resources/scripts/";
		private: //Temp
			bool m_bLoaded = false;
			void attachFunctions(lua_State * L);
			void attachClasses(lua_State* L);
		private:
			void readRootTable(lua_State* L);	//!< Read the root table
			std::shared_ptr<Entity> readEntity(sol::table t);

			lua_State* m_RunState;	//!< Script for lua game loop
		public:
			LuaScripting();

			void process(std::vector<std::shared_ptr<Entity>>* entity);
			void update(float dt) override;

			//---Message Receiver--//
			void processMessages(const std::vector<std::shared_ptr<Message>>* msgs);
		};
	}
};
