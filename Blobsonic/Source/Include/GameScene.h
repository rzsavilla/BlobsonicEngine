/**
* @class	GameScene
* @brief	Game Scene updates, runs and draws game loop
* Game Scenes stores game objects and logic.
* The Scene stores game objects, and updates objects and game logic.
*/

#pragma once

#include "Scene.h"

#include "ModelOLD.h"
#include "Light.h"
#include "QuatCamera.h"
#include "MyRobot.h"
#include "Component.h"
#include "MyTimer.h"
#include "Text.h"
#include "Button.h"

//physics
#include "OBB.h"
#include "AABB.h"
#include "Sphere.h"

class GameScene: public Scene {
public:
	GameScene()
	{
		
	}

	void initScene() override { };

	void update(float dt) override { };
};

/*
class GameScene :public Scene {
private:
	std::vector<std::pair<std::string, Model>> m_vModels;		//!< Store Models with id
	std::vector<std::pair<std::string, Light>> m_vLights;		//!< Store Lights with id
	std::vector<std::pair<std::string, QuatCamera>> m_vCamera;	//!< Store Cameras with id
	std::vector<std::pair<std::string, MyRobot>> m_vRobots;		//!< Store Robots with id
	std::vector<std::pair<std::string, Button>> m_vButton;		//!< Store buttons with id
	std::vector<std::pair<std::string, OBB>> m_vOBB;    //!< Store Physics
	std::vector<std::pair<std::string, AABB>> m_vAABB;    //!< Store Physics
	std::vector<std::pair<std::string, Sphere>> m_vSphere;    //!< Store Physics

	void updateCamera(std::shared_ptr<GLSLProgram> shader, QuatCamera cam);		//!< Passes camera uniforms to shader program
	void updateLights(std::shared_ptr<GLSLProgram> shader);						//!< Passes lights uniforms  to shader program

	double m_dDeltaMouseX;	//!< Mouse position difference X
	double m_dDeltaMouseY;	//!< Mouse position difference Y

	void nextCamera();		//!< Switch active camera to next camera
	void prevCamera();		//!< Switch active camera to previous camera

	MyTimer m_camSwitchDelay;	//!< Delay timer for switching cameras

	//! Calculates distance between robot and model to determine if a collision has occured
	bool collision(MyRobot* robot, Model* model);

	std::shared_ptr<Text> m_PickupCounterText;	//!< Text object for
	int m_iTotalPickups;		//!< Total number of pickups when scene is initialized
	int m_iCollected;			//!< Tracks the number of pickups collected in the scene
public:
	GameScene();		//!< Default Constructor

	void addModel(std::pair<std::string, Model> model);				//!< Add model into the scene
	void addLight(std::pair<std::string, Light> light);				//!< Add light into the scene
	void addCamera(std::pair<std::string, QuatCamera> camera);		//!< Add light into the scene only one camera can be active
	void addRobot(std::pair<std::string, MyRobot> robot);			//!< Add robot into the scene currenly only uses the first element
	void addPhysical(std::pair<std::string, Model> model);			//!< Add  pyscis object into the scene
	void addButton(std::pair<std::string, Button> button);			//!< Add robot into the scene currenly only uses the first element

	void initScene();							//!< Initialize scene
	void handleInput(GLFWwindow* window);		//!< Handle user inputs
	void update(float dt);						//!< Update scene
	void checkForCollision(float dt);			//!<Check through objects for collision
	void draw();								//!< Draw scene
};

*/