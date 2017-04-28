/*
*	@class LuaScripting
*	@brief System handles lua scripts.
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
		lua_State* m_luaState;	//!< Lua State, stores loaded script

		void loadScript(std::string luaFile);		//!< Load .lua script file store into state
	
		void addFunctions();

		void helloWorld();

	private:	//Functions that can be called by lua

	public:
		LuaScripting();
		
		void process(std::vector<std::shared_ptr<Entity>>* entity) override;
		void update(float dt) override;

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
};
