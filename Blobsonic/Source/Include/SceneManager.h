/**
* @class	Scene
* @brief	Storage for scenes and determines active scene
* @author	Rozen Savilla
* Storage for loaded scenes ready to be activated
*/

#pragma once

#include "Scene.h"
#include "ResourceManager.h"

class SceneManager {
private:
	std::string m_sActiveScene;									//<! ID/Name of active scene
	std::map<std::string, std::shared_ptr<Scene>> m_scenes;		//!< Store scenes
public:
	SceneManager(ResourceManager* res);	//!< Defualt constructor

	bool setActiveScene(std::string name);		//!< Set active scene

	bool hasScene(std::string name);			//!<Returns true if scene os stored within the manager

	void addScene(std::string name, std::shared_ptr<Scene> scene);	//!< Add a scene into the scene manager
	void removeScene(std::string name);								//!< Remove scene from scene manager/Destroys

	std::shared_ptr<Scene> getActiveScene();						//!< Returns active scene
};