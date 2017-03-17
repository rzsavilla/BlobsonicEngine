/**
* @class	SceneComponent
* @brief	Stores scenes
* Stores a list of scenes allowing for easy scene loading and switching.
* Will update and load scenes as well as resources
*/

/*
Text Rendering code
https://learnopengl.com/#!In-Practice/Text-Rendering
*/

#pragma once

#include "Component.h"
#include "Text.h"
/*
class SceneComponent: public Component::Component {
private:
	GLFWwindow *m_ptrWindow;			//!< Game window
	ResourceManager m_res;				//!< Stores all game resources
	std::vector<std::pair<std::string, std::shared_ptr<Scene>>> m_scenes;	//!<Stores all scenes with id
	//std::map<GLchar, Character> m_Characters;		//!< Freetype characters used to create text	

	unsigned int m_uiActiveScene;		//!< Index for the active scene
	bool m_bWindowLoaded = false;		//!< Flag for checking if window has already been loaded, prevents reinialization when reloading scenes
	bool m_bReload = false;				//!<Flag for reloading the scene/ *fix ensures render component is empty
	void handleInput();		//!< Process GLFW inputs for active scene

	//std::shared_ptr<Text> m_FPSText;	//!< Text displays FPS

	//std::shared_ptr<Text> getTextObject(std::string id);		//!< Finds and returns text object
	//std::vector<std::pair<std::string,std::shared_ptr<Text>>> m_vTexts;		//!< Stores text
public:
	void init();	//!< initialize component
	void handleMessage(std::shared_ptr<Message> msg);	//!< Handle messages received
	void update(float dt);								//!< Update component
};

*/