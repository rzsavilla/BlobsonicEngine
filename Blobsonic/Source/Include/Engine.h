/*
//Singleton using smartpointer implementation guide
http://silviuardelean.ro/2012/06/05/few-singleton-approaches/

//Component based engine design
http://www.randygaul.net/2013/05/20/component-based-engine-design/
*/

/**
* @class	Engine
* @brief	Stores engine components
* Only a single Engine instance can exist (Singleton).
* The Engine has components that are attached to it when running the Engine updates all of its components
* and stores a list of messages that each component has a pointer to allowing them to create messages of 
* their own in order to communicate with all the other components attached to the Engine
*/

#pragma once

#include <stdafx.h>
#include <memory>
#include <mutex>
#include "Render.h"
#include "SceneLoader.h"

class Engine {
private:
	//////Singleton///////
	Engine();		//!< Private Constructor
	static bool m_bInstance;						//!< Instance flag
	static std::shared_ptr<Engine>& m_ptrInstance;	//!< Pointer to instance
	/////Component Functions/Variables///////
	std::vector<std::unique_ptr<Component>> m_ptrComponents;	//!< Stores all components object has.
	std::vector<std::shared_ptr<Message>> m_vMessages;			//!< Stores all messages created by components

	void handleMessages();	//!< Passes messages to all engine components
	bool m_bRunning;		//!< Flag for if engine is running
public:
	
	//////Singleton///////
	~Engine();		//!< Destructor
	static std::shared_ptr<Engine>& getInstance();	//!< Returns pointer to engine instance

	//! Attaches a component
	void attachComponent(std::unique_ptr<Component> newComponent) {
		m_ptrComponents.push_back(std::move(newComponent));
		m_ptrComponents.back()->setLocalMsgPtr(&m_vMessages);
	}

	void init();		//!< Initialize engine
	void run();			//!< Starts the engine loop
};