/*
*	@class LuaScripting
*	@brief System handles lua scripts.
*	@author Rozen Savilla
*	Handles loading and using lua scripts acts as an interface to lua to call C++ functions/class
*/

/*
	Using Lua with C++ tutorial
	https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/
	
	Code for getting lua table data:
	https://eliasdaler.wordpress.com/2014/07/18/using-lua-with-cpp-luabridge/
*/

#pragma once

#include "System.h"
#include <iostream>

namespace System {
	namespace Scripting {
		class LuaScripting : public System {
		private:
			const bool m_bDebug = true;	//For couts
			const std::string m_scriptsDir = "Source/Resources/scripts/";
		private: //Temp
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
