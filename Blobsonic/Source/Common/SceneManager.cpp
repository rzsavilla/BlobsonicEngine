#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	//Set all scene to be destroyed
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		(*it)->destroy();
	}
	m_scenes.clear();	//Remove all pointers to scene
}

std::shared_ptr<SceneManager> SceneManager::getInstance()
{
	static std::shared_ptr<SceneManager> instance = nullptr;

	if (!instance) {
		instance.reset(new SceneManager);
	}
	return instance;
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

void SceneManager::destroyActiveScene()
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		if ((*it)->getName() == m_sActiveScene) {
			(*it)->clearScene();	//!< Destroy all entities within scene
			m_scenes.erase(it);	//Remove scene
			return;
		}
	}
}

bool SceneManager::hasScene(int uniqueID)
{
	return false;
}

bool SceneManager::hasScene(std::string name)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		if ((*it)->getName() == name) {
			return true;	//Scene exists
		}
	}
	return false;
}

void SceneManager::addActiveScene(std::shared_ptr<Scene> scene)
{
	m_sActiveScene = scene->getName();
	m_scenes.push_back(scene);
}

void SceneManager::addScene(std::shared_ptr<Scene> scene)
{
	m_scenes.push_back(scene);
}

void SceneManager::removeScene(std::string name)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		if ((*it)->getName() == name) {
			m_scenes.erase(it);
		}
	}
}

std::shared_ptr<Scene> SceneManager::getActiveScene()
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
		if ((*it)->getName() == m_sActiveScene) {
			return (*it);	//Return scene
		}
	}
	return NULL; //No Active Scene
}
