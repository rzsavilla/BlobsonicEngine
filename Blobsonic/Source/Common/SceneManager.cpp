#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_State = Active;
	m_bHasLoadingScreen = false;
	m_bForceReloadResouces = false;
	m_bLock = false;
}

SceneManager::~SceneManager()
{
	m_ActiveScene->clearScene();
	m_LoadingScene->clearScene();

	m_ActiveScene->destroy();
	m_LoadingScene->destroy();
}

std::shared_ptr<SceneManager> SceneManager::getInstance()
{
	static std::shared_ptr<SceneManager> instance = nullptr;

	if (!instance) {
		instance.reset(new SceneManager);
	}
	return instance;
}

void SceneManager::setLoadingScene(std::string filename)
{
	m_bHasLoadingScreen = true;
	m_sLoadingScene = filename;
}

void SceneManager::changeScene(std::string filename, bool reloadResources)
{
	if (m_State == Active) {
		m_bForceReloadResouces = reloadResources;
		m_transitionTimer.reset();
		m_sActiveScene = filename;
		if (m_ActiveScene)	m_ActiveScene->clearScene();
		if (m_LoadingScene) m_LoadingScene->clearScene();
		m_ActiveScene = std::make_shared<Scene>();
		
		if (!m_sLoadingScene.empty()) m_LoadingScene = m_loader.fastLoadScene(m_sLoadingScene);

		m_State = Loading;
	}
}

void SceneManager::lock(bool state)
{
	m_bLock = state;
}

void SceneManager::update()
{
	if (m_State == Loading) {
		if (m_loader.loadScene(m_ActiveScene, m_sActiveScene, m_bForceReloadResouces)) {
			//Scene has finished loading
			m_State = Loaded;
		}
	}
	else if (m_State == Loaded) {
		std::cout << "Loaded\n";
		//State has finished Loading
		if ((m_transitionTimer.getElapsed() > m_fTransitionDelay)) {
			m_State = Active;
			std::cout << "Transition Timer: " << m_transitionTimer.getElapsed() << "\n";
		}
	}

	//Remove Destoyed entities
	if (m_ActiveScene) m_ActiveScene->getEntityManager()->updateEntityManager();
	if (m_LoadingScene) m_LoadingScene->getEntityManager()->updateEntityManager();
}

void SceneManager::reload()
{
	changeScene(m_sActiveScene);
}

std::shared_ptr<Scene> SceneManager::getActiveScene()
{
	if (m_State == Active) {
		if (!m_bLock) {
			if (m_ActiveScene) return m_ActiveScene;
		}
	}
	if (m_LoadingScene) return m_LoadingScene;
	else  return NULL; //No Scene
}

std::string SceneManager::getActiveSceneName()
{
	return m_sActiveScene;
}

SceneManagerState SceneManager::getState()
{
	return m_State;
}
