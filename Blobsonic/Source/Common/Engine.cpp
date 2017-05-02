#include <stdafx.h>
#include "Engine.h"
#include "ModelOLD.h"
#include "Transformable.h"
#include "Camera.h"
#include "Render.h"
#include "EngineMessages.h"

#include "InputMessages.h"
#include "SceneMessages.h"

void Engine::Engine::initScene(bool forceReloadRes)
{
	std::cout << "\n----------Initialize Scene----------\n\n";
 
	m_SceneManager->destroyActiveScene();
	m_SceneManager->addActiveScene(
		m_sceneLoader.fastLoadScene("Source\\Resources\\scenes\\MainMenu.xml", forceReloadRes));
	std::cout << "\n----------Scene Initialized----------\n\n";
	m_bReloadScene = false;
	m_bForceReload = false;
	m_bMainMenu = true;
}

void Engine::Engine::loop()
{
	double dFPSLimit = 1.0 / 60.0;

	double dPrevTime = glfwGetTime();
	double dTimer = dPrevTime;
	double dt = 0.0;
	double dCurrentTime = 0;
	int iFrames = 0;
	int iUpdates = 0;

	m_deltaTimer.reset();
	while (m_bRunning) {
		//Calculate delta time
		dCurrentTime = glfwGetTime();
		dt += (dCurrentTime - dPrevTime) / dFPSLimit;
		dPrevTime = dCurrentTime;

		if (m_bReloadScene) initScene();			//Reload scene
		else if (m_bForceReload) initScene(true);	//Reload scene including scene resources

		
		//Simply measures how much more time is left before the next update/physics test is calculated
		//This means that the system framerate does not effect physics etc.
		//Removed the need for dt being passed through update.
		while (dt >= 1.0) {
			update((float)m_deltaTimer.getElapsed());
			iUpdates++;
			dt--;
		}

		//Render
		render();
		iFrames++;	//Count frames

		glfwSwapInterval(0);		//VSYNC
		glfwSwapBuffers(m_window);

		glfwPollEvents();

		MessageHandler::getInstance()->notify();

		//Reset every second
		if (glfwGetTime() - dTimer > 1.0) {
			//std::cout << "FPS:" << iFrames << "\n";
			dTimer++;
			iUpdates = 0;
			iFrames = 0;
		}
		m_deltaTimer.reset();
	}

	//Close window and terminate GLFW
	glfwTerminate();
}

void Engine::Engine::update(float dt)
{
	//Get Active Scene
	std::shared_ptr<Scene> m_activeScene = m_SceneManager->getActiveScene();
	if (m_activeScene) {
		//Pass scene entities to systems
		for (auto it = m_ptrSystems.begin(); it != m_ptrSystems.end(); ++it) {
			if (it->first != typeid(System::Render)) {	//Do not process render systems
				//--System process entities--//
				(*it).second->process(m_activeScene->getEntities());
			}
		}

		for (auto it = m_ptrSystems.begin(); it != m_ptrSystems.end(); ++it) {
			if (it->first != typeid(System::Render)) {	//Do not process render systems
				//Update Systems
				(*it).second->update(dt);
			}
		}
	}
}

void Engine::Engine::render()
{
	//Clear Screen
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Get Active Scene
	std::shared_ptr<Scene> m_activeScene = m_SceneManager->getActiveScene();
	//Render systems process
	if (m_activeScene) {
		for (auto it = m_ptrSystems.begin(); it != m_ptrSystems.end(); ++it) {
			if (it->first == typeid(System::Render)) {	//Only process render systems
				//Render entities
				(*it).second->process(m_activeScene->getEntities());
				//Update Render System
				(*it).second->update(0.0f);	
			}
		}
	}
}

Engine::Engine::Engine()
{
	m_bRunning = false;
	m_SceneManager = SceneManager::getInstance();
}

void Engine::Engine::init(int width, int height)
{
	MessageHandler::getInstance()->attachReceiver(this);

	m_iWindowWidth = width;
	m_iWindowHeight = height;
	m_sWindowTitle = "Game Engine";
	//---------------------------GLWF---------------------//
	//Initialize GLFW 
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);		//Enable Depth buffer

	//Open Window
	m_window = glfwCreateWindow(m_iWindowWidth, m_iWindowHeight, m_sWindowTitle.c_str(), NULL, NULL);

	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, key_callback);

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_HAND_CURSOR); /// Sets the mouse to be enabled
	
	//Tell systems a window has been set
	MessageHandler::getInstance()->sendMessage(std::make_shared<EngineMessage::SetWindow>(m_window));

	if (m_window == NULL) {
		std::cout << "Failed to load window\n";
		system("pause");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
	//Load OpenGL functions
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if (!didLoad) {
		//Clean up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	
	gl::Enable(gl::DEPTH_TEST);

	initScene(true);

	glfwSetCursorPos(m_window, m_iWindowWidth/2, m_iWindowHeight/2); /// Sets the Cursor position to be the middle of the screen.

	glfwSwapInterval(1);
}

void Engine::Engine::run()
{
	//Start Game loop
	m_bRunning = true;
	this->loop();
}

void Engine::Engine::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	//Create Input Messages
	for (int i = 0; i < msgs->size(); i++) {
		std::string s = msgs->at(i)->sID;

		double xpos, ypos;
		glfwGetCursorPos(m_window, &xpos, &ypos);

		if (s == "Input_KeyPress") {
			//Get data key data from message
			auto data = static_cast<InputMessage::KeyPress*>(msgs->at(i).get());
			if (data->m_iAction == GLFW_PRESS || data->m_iAction == GLFW_REPEAT) {	//Key is pressed
				switch (data->m_iKey)
				{
				case GLFW_KEY_ESCAPE:
					m_bRunning = false;	//End game loop
					break;
				case GLFW_KEY_P:
					m_bReloadScene = true;	//Reload scene objects
					break;
				case GLFW_KEY_O:
					m_bForceReload = true;	//Reload entire scene including resources
				case GLFW_KEY_I:			//Reload scene and scripts
					m_bReloadScene = true;
					MessageHandler::getInstance()->sendMessage<SceneMessage::Reload>();
				case GLFW_KEY_1:
					if (m_bMainMenu == true)
					{
						/// Gets the Cursor position
						bool inBounds(int value, int low, int high);
						if (xpos >= 20 && xpos <= 220 && ypos >= 20 && ypos <= 120)
						{
							std::cout << "Button Pressed: " << xpos << ", " << ypos << "\n";
							m_SceneManager->destroyActiveScene();
							m_SceneManager->addActiveScene(m_sceneLoader.fastLoadScene("Source\\Resources\\scenes\\WorldTest.xml", false));
							std::cout << "\n----------Scene Initialized----------\n\n";
							m_bReloadScene = false;
							m_bForceReload = false;
							m_bMainMenu = false;
						}
						else
						{
						std::cout << "Button Not Pressed " << "\n";
						}
					}	
					break;
				default:
					break;
				}
			}
		}
		else if (s == "AddEntity") {
			//Add Entity to active scene
			auto data = static_cast<SceneMessage::AddEntity*>(msgs->at(i).get());
			auto activeScene = m_SceneManager->getActiveScene();
			if (activeScene) {
				activeScene->getEntityManager()->addEntity(data->entity);
			}
		}
	}
}