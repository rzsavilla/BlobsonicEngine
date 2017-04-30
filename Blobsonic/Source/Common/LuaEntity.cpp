#include "stdafx.h"
#include "LuaEntity.h"

#include "SceneMessages.h"

//Components
#include "Player.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Transformable.h"

static std::shared_ptr<EntityFactory> m_EntityFactory = std::make_shared<EntityFactory>();

LuaEntity::LuaEntity()
{
	std::cout << "---New Lua Entity---\n";
	m_entity = std::make_shared<Entity>();	//Instatiate entity
	MessageHandler::getInstance()->sendMessage<SceneMessage::AddEntity>(m_entity);	
}

void LuaEntity::attachComponent(const std::string& sComponent)
{
	if (m_bDebug) std::cout << "LuaEntity:" << getID() << " ";
	if (sComponent == "Transformable") {
		m_entity->attach<Component::Transformable>();
		if (m_bDebug) std::cout << " - Transformable\n";
	}
	else if (sComponent == "Player") {
		m_entity->destroy();
		m_entity = m_EntityFactory->createPlayer(glm::vec3 (0.0f,0.0f,0.0f));
		MessageHandler::getInstance()->sendMessage<SceneMessage::AddEntity>(m_entity);
		if (m_bDebug) std::cout << " - Player\n";
	}
	else if (sComponent == "DirectionalLight") {
		m_entity->attach<Component::DirectionalLight>();
		if (m_bDebug) std::cout << " - DirectionalLight\n";
	}
}

unsigned int LuaEntity::getID()
{
	return m_entity->getUID();
}

void LuaEntity::register_lua(luabridge::lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L).
		beginClass<LuaEntity>("LuaEntity")
		.addConstructor<void(*)()>()
		.addFunction("attachComponent",&LuaEntity::attachComponent)
		.addFunction("getID",&LuaEntity::getID)
		.endClass();
}
