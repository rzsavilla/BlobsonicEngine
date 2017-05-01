/**
* @class	Scene
* @brief	Storage for scenes and determines active scene
* @author	Rozen Savilla
* Storage for loaded scenes ready to be activated
*/

#pragma once

#include "Scene.h"

class SceneManager {
private:
	std::string m_sActiveScene;						//!< ID/Name of active scene
	std::vector<std::shared_ptr<Scene>> m_scenes;	//!< Scene storage

	SceneManager();	//!< Private default constructor Singleton
public:
	~SceneManager();	//!< Destructor

	static std::shared_ptr<SceneManager> getInstance();		//!< Return class instance

	bool setActiveScene(std::string name);		//!< Set active scene
	void destroyActiveScene();					//!< Destroys the active scene

	bool hasScene(int uniqueID);					//!< Check if scene exists search by UID
	bool hasScene(std::string name);	//!< Check if scene exists search by name

	void addActiveScene(std::shared_ptr<Scene> scene);		//!< Add new scene and set it as active scene. Will also destroy current active scene

	void addScene(std::shared_ptr<Scene> scene);	//!< Add a scene into the scene manager
	void removeScene(std::string name);								//!< Remove scene from scene manager/Destroys

	std::shared_ptr<Scene> getActiveScene();						//!< Returns active scene
};