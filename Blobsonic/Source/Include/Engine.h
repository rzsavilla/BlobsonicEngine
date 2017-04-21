#pragma once

#include <stdafx.h>
#include <memory>
#include "MessageHandler.h"
#include "InputMessages.h"
#include "System.h"

#include "TestScene.h"

#include "SceneLoader.h"

#include "EntityManager.h"
#include "ResourceManager.h"

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

		ResourceManager m_resourceManager;
		void loadResources();

	private:
		//TestScene m_TestScene;
		SceneLoader m_sceneLoader;
		std::map<std::string, std::shared_ptr<Scene>> m_scenes;
		void initScene();	//!< Initialize Scene
	private:	//GLFW
		int m_iWindowWidth;
		int m_iWindowHeight;
		std::string m_sWindowTitle;
		GLFWwindow* m_window;		//!< GLFW Window
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