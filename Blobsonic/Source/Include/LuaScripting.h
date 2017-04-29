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

extern "C" {
	# include "lua.h"
	# include "lauxlib.h"
	# include "lualib.h"
}

using namespace luabridge;

namespace System {
	class LuaScripting: public System {
	private:
		const std::string m_scriptsDir = "Source/Resources/scripts/";

		lua_State* m_luaState;	//!< Lua State, stores loaded script
		void loadScript(std::string luaFile);		//!< Load .lua script file store into state
		
		void registerFunctions();
	private:	//Functions that can be called by lua

		std::shared_ptr<Entity> Entity_new(lua_State* L);	//!Lua function call to create new entity object
	public:
		LuaScripting();
		
		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
};
