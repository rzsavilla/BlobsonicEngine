/**
* @class	Scene
* @brief	Storage for scenes and determines active scene
* @author	Rozen Savilla
* Prepares/loads scene stores them and determines active scene
*/

#pragma once

#include "Scene.h"
#include "SceneLoader.h"
#include "MyTimer.h"

//! Scene Manager States
enum SceneManagerState {
	Loading,
	Active,
	Loaded,
};

class SceneManager {
private:

	const float m_fTransitionDelay = 0.0f;			//!< Minimum time elapsed before transitioning to the next scene
	bool m_bForceReloadResouces;		//!< Flag to reload scene resourcefile
private:
	std::string m_sActiveScene;						//!< ID/Name of active scene
	std::shared_ptr<Scene> m_ActiveScene;			//!< Loaded active Scene
	std::shared_ptr<Scene> m_LoadingScene;			//!< Loading Scene

	SceneLoader m_loader;	//!< Loads scene files
	SceneManagerState m_State;	//!< Current scene state

	//---Loading-----Scene
	bool m_bHasLoadingScreen;		//!< Flag to determine if scene manager has a loading screen
	std::string m_sLoadingScene;	//!< Scene file for loading scene

	SceneManager();	//!< Private default constructor Singleton
	
	MyTimer m_transitionTimer;	//!< Counts delay when changing scene

	bool m_bLock;	//!< If true scene will not automatically switch to changed scene. (To allow scripts to intialize first)
public:
	~SceneManager();	//!< Destructor

	static std::shared_ptr<SceneManager> getInstance();		//!< Return class instance

	void setLoadingScene(std::string filename);	//!< Set the filename of the loading scene

	void changeScene(std::string filename, bool reloadResources = false /* default false Force reload all resources */);

	/*! Lock, true - stops the scene switch from loading to activescene automatically
	*	Lock, false - stops allows scene to switch to active scene from loading scene
	*/
	void lock(bool state);	

	void update();	//!< Update scene manager

	void reload();	//!< Reload current active scene

	std::shared_ptr<Scene> getActiveScene();						//!< Returns active scene
	std::string getActiveSceneName();		//!< Return file name of active scene

	SceneManagerState getState();	//!< Return current scene manager state
};