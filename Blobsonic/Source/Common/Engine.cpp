#include <stdafx.h>
#include "Engine.h"
#include "MyTimer.h"

Engine::Engine()
{

}

void Engine::handleMessages()
{
	//Iterate through components
	for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {

		//Send messages to components
		for (int i = 0; i < m_vMessages.size(); i++) {
			(*it)->handleMessage(m_vMessages.at(i)); //Components will handle the messages
		}
	}

	//Engine reads messages
	std::string s;
	for (int i = 0; i < m_vMessages.size(); i++) {
		s = m_vMessages.at(i)->sID;
		if (s == "Scene_Exit") {
			m_bRunning = false;
		}
	}

	m_vMessages.clear();		//Remove all messages
}

Engine::~Engine()
{

}

std::shared_ptr<Engine>& Engine::getInstance()
{
	static std::shared_ptr<Engine> instance = nullptr;

	if (!instance)
	{
		if (!instance) {
			instance.reset(new Engine());
		}
	}

	return instance;
}

void Engine::init()
{
	m_bRunning = true;

	//Initialize attached components
	for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			(*it)->init();
	}

	handleMessages();
}

void Engine::run()
{
	//Timestep
	MyTimer dtTimer;
	float currentTime = 0.0f;
	float fOldTime = 0.0f;

	//Frame counter
	MyTimer fpsTimer;
	int iTotalFrames = 0;

	while (m_bRunning) {
		currentTime = dtTimer.getElapsed();
		float dt = currentTime - fOldTime;
		fOldTime = currentTime;

		handleMessages();	//Pass messages to components
		//Update components
		for (auto it = m_ptrComponents.begin(); it != m_ptrComponents.end(); ++it) {
			(*it)->update(dt);
		}
		glfwPollEvents();

		//When 1 second has passed
		if (fpsTimer.getElapsed() > 1.0f) {	
			//Pass frames to components
			m_vMessages.push_back(std::make_shared<EngineMessage::FrameCount>(iTotalFrames));
			//std::cout << iTotalFrames << "\n";
			iTotalFrames = 0;	//Reset frame count
			fpsTimer.reset();
		}
		else {
			//Count frame
			iTotalFrames++;
		}
	}
}