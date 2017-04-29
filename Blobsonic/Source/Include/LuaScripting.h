/*
*	@class LuaScripting
*	@brief System handles lua scripts.
*	@author Rozen Savilla
*	Handles loading and using lua scripts acts as an interface to lua to call C++ functions/class
*/

/*
	Using Lua with C++ tutorial
	https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/
*/

#pragma once

#include "System.h"

#include <LuaBridge.h>
#include <iostream>

#include "System.h"

extern "C" {
	# include "lua.h"
	# include "lauxlib.h"
	# include "lualib.h"
}

using namespace luabridge;

namespace System {
	namespace Scripting {
		class LuaScripting : public System {
		private:
			const bool m_bDebug = true;	//For couts

			const std::string m_scriptsDir = "Source/Resources/scripts/";

			lua_State* m_luaState;	//!< Lua State, stores loaded script
			void loadScript(std::string luaFile);		//!< Load .lua script file store into state

			void registerFunctions(lua_State* L);
			void registerClasses(lua_State* L);
		private:	//Functions that can be called by lua

			//Temp
			bool m_bLoaded = false;
		public:
			LuaScripting();

			void process(std::vector<std::shared_ptr<Entity>>* entity) override;
			void update(float dt) override;

			//---Message Receiver--//
			void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
		};
	}
};
