#include <stdafx.h>
#include "Engine.h"
#include "ModelOLD.h"
#include "Transformable.h"
#include "Camera.h"
#include "Render.h"
#include "EngineMessages.h"

#include "InputMessages.h"

void Engine::Engine::loadResources()
{
	m_TestScene.initScene();
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
	while (m_bRunning) {
		//Calculate delta time
		dCurrentTime = glfwGetTime();
		dt += (dCurrentTime - dPrevTime) / dFPSLimit;
		dPrevTime = dCurrentTime;

		//Limit update
		while (dt >= 1.0) {
			update((float)dt);
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
			std::cout << "FPS:" << iFrames << "\n";
			dTimer++;
			iUpdates = 0;
			iFrames = 0;
		}
	}

	////Close window and terminate GLFW
	glfwTerminate();
}

void Engine::Engine::update(float dt)
{
	for (auto it = m_ptrSystems.begin(); it != m_ptrSystems.end(); ++it) {
		if (it->first != typeid(System::Render)) {	//Do not process render systems
			//--System process entities--//
			(*it).second->process(m_scenes.find("game_scene")->second->getEntities());
		}
	}

	for (auto it = m_ptrSystems.begin(); it != m_ptrSystems.end(); ++it) {
		if (it->first != typeid(System::Render)) {	//Do not process render systems
			//Update Systems
			(*it).second->update(dt);
		}
	}
}

void Engine::Engine::render()
{
	//Clear Screen
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Render systems process
	for (auto it = m_ptrSystems.begin(); it != m_ptrSystems.end(); ++it) {
		if (it->first == typeid(System::Render)) {	//Only process render systems
			//Render entities
			(*it).second->process(m_scenes.find("game_scene")->second->getEntities());
		}
	}
}

Engine::Engine::Engine()
	:m_TestScene(&m_resourceManager)
	,m_sceneLoader(&m_resourceManager,&m_scenes)
{
	m_bRunning = false;
}

void Engine::Engine::init(int width, int height)
{
	MessageHandler::getInstance()->attachReceiver(this);

	m_iWindowWidth = width;
	m_iWindowHeight = height;
	m_sWindowTitle = "Game Engine";
	//----------------------------GLWF---------------------//
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

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	gl::Enable(gl::DEPTH_TEST);
	gl::Enable(gl::CULL_FACE);
	gl::CullFace(gl::BACK);

	m_sceneLoader.load("Source\\Resources\\scenes\\test.xml");
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

		if (s == "Input_KeyPress") {
			//Get data key data from message
			auto data = static_cast<InputMessage::KeyPress*>(msgs->at(i).get());
			if (data->m_iAction == GLFW_PRESS || data->m_iAction == GLFW_REPEAT) {	//Key is pressed
				switch (data->m_iKey)
				{
				case GLFW_KEY_ESCAPE:
					m_bRunning = false;	//End game loop
					break;
				default:
					break;
				}
			}
		}
	}
}