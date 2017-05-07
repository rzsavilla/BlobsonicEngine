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

namespace System {
	namespace Scripting {
		class LuaScripting : public System {
		private:
			const bool m_bDebug = true;	//!< For couts to the console 
			std::shared_ptr<SceneManager> m_SceneManager;	//!< Pointer so scene manager
			const std::string m_scriptsDir = "Source/Resources/scripts/";	//!< Location of script files
		private:
			//lua_State* m_RunState;
			lua_State* m_RunState;	//!< Script for lua game loop
		private:
			//-----------------Register----------------------------
			void registerFunctions(lua_State * L);	//!< register functions to lua state
			void registerClasses(lua_State* L);		//!< Register classes and member functions/variables to lua state
			
			//-----------------Scene Management--------------------
			void setLoadingScene(std::string sceneFile);	//!< Set scene shown when loading next scene
			void changeScene(std::string sceneFile);		//!< Load and change to a specified scene
			void reloadScene();				//!< Set loading scene
			void forceReloadScene();		//!< Reload scene including all resources
			std::string getActiveScene();	//!< Retun the name of the active scene
			void destroyEntity(unsigned int ID);	//!< Destroy a scene entity by ID

			//-----------------Inputs------------------------------
			bool isKeyDown(const std::string& key);			//!< Check if a key is pressed
			bool isMouseDown(const std::string& button);	//!< Check if a mouse button is down
			void hideCursor(bool hide);						//!< Enable or disable mouse cursor
			//-----------------Misc------------------------------
			void printString(const std::string& s);	//!< Function simply prints string into console
			int print(lua_State* L);				//! Replace lua print function
		public:
			LuaScripting();	//!< Default constructor
			//Scene management
			static bool m_bReloadScene;			//!< Flag Reload scene xml and all objects
			static bool m_bReloadScripts;		//!< Flag Reload scripts
		
			//! Process all entities
			void process(std::vector<std::shared_ptr<Entity>>* entity) override;
			//! Update system
			void update(float dt) override;

			//! Process messages//
			void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
		};
	}
};
