#include "stdafx.h"
#include "LuaScripting.h"
#include "Entity.h"

#include "InputMessages.h"
#include "SceneMessages.h"

#include "Component.h"
#include "Transformable.h"

#include "Player.h"
#include "LuaEntity.h"

System::Scripting::LuaScripting::LuaScripting()
{
	MessageHandler::getInstance()->attachReceiver(this);
}

void System::Scripting::LuaScripting::process(std::vector<std::shared_ptr<Entity>>* entity)
{

}

void System::Scripting::LuaScripting::update(float dt)
{
	if (!m_bLoaded) {

		m_bLoaded = true;
	}
}

void System::Scripting::LuaScripting::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "Scene_Reload") {
			//Reload scripts
			std::cout << "Reload Scripts\n";
			if (m_bLoaded) m_bLoaded = false;
		}
	}
}
