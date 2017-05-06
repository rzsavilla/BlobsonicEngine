#pragma once

#include "MessageHandler.h"
#include "InputMessages.h"
#include "System.h"
#include "SceneLoader.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include "MyTimer.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	MessageHandler::getInstance()->sendMessage(std::make_shared<InputMessage::KeyPress>(key, action));
}

namespace Engine {
	class Engine : public MessageReceiver {
	private:
		//! Stores ptr to engine system
		std::map<std::type_index, std::shared_ptr<System::System>> m_ptrSystems;
		bool m_bRunning;	//!< Flag to start and end game loop

		MyTimer m_deltaTimer;

		std::shared_ptr<ResourceManager> m_resourceManager;
	private:
		bool m_bReloadScene;	//!< Flag for xml scene intialization
		bool m_bForceReload;	//!< Flag for xml scene loading forcing resources to be reloaded
		
		SceneLoader m_sceneLoader;		//!< Responsible for loading scene/xml files
		std::shared_ptr<SceneManager> m_SceneManager;	//!< Manages all scenes

		void initScene(/*! Optional default is false*/bool forceReloadRes = false);	//!< Initialize Scene
	private:	//GLFW
		int m_iWindowWidth;
		int m_iWindowHeight;
		std::string m_sWindowTitle;
		GLFWwindow* m_window;		//!< GLFW Window
		bool m_bIsFullScreen;		//!< Flag to determine if window is fullscreen or windowed
	private:
		bool m_bIsInitialized;

		void loop();			//!< Game Loop
		void update(float dt);	//!< System updates
		void render();			//!< System draw calls
	public:
		Engine();		//!< Default constructor

		template<typename T, typename... Args>
		void attachSystem(Args &&...args) {
			m_ptrSystems[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		void detachSystem() {
			m_ptrSystems.erase(typeid(T));
		}

		void init(int width, int height); //!< Initialize Engine
		void run();						//!< Start Game loop

		//---Message Receiver--//
		void processMessages(const std::vector<std::shared_ptr<Message>>* msgs) override;
	};
}