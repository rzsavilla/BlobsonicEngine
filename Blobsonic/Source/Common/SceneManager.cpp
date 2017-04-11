#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{

}

bool SceneManager::setActiveScene(std::string name)
{
	if (this->hasScene(name)) {
		m_sActiveScene = name;
		return true;
	}
	else {
		return false;
	}
}

bool SceneManager::hasScene(std::string name)
{
	return m_scenes.find(name) != m_scenes.end();
}

void SceneManager::addScene(std::string name, std::shared_ptr<Scene> scene)
{
	m_scenes.emplace(name, scene);
}

void SceneManager::removeScene(std::string name)
{
	m_scenes.erase(name);
}

std::shared_ptr<Scene> SceneManager::getActiveScene()
{
	return m_scenes.find(m_sActiveScene)->second;
}
