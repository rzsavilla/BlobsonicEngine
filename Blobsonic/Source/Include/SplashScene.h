/**
* @class	SplashScene
* @brief	Displays a simple splash/loading screen
* Briefly shows a scene then moves onto the game scene
*/

#pragma once

#include "Scene.h"
#include "MyTimer.h"
#include "Text.h"
class SplashScene {
private:
	MyTimer timer;							//!< Timer for when to switch scenes
	//std::shared_ptr<Text> m_LoadingText;	//!< Splash screen loading text
public:
	SplashScene();
	void initScene();						//!< Initialize scene
	void handleInput(GLFWwindow* window);	//!< Handle user input
	void update(float dt);					//!< Update sene
	void draw();							//!< Draw scene
};