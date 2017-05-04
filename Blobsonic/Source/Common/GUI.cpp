#include "stdafx.h"
#include "Button.h"
#include "SpriteRender.h"
#include "GUI.h"
#include "Transformable.h"
#include "Message.h"
#include "SceneManager.h"
#include "Text.h"
//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cursor callback functions
/// 
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
void cursorEnterCallback(GLFWwindow *window, int entered);

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
	std::cout << xPos << " : " << yPos << "\n";
}

void cursorEnterCallback(GLFWwindow * window, int entered)
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void System::GUI::addEntity(std::shared_ptr<Entity> entity, std::vector<std::shared_ptr<Entity>>* entities)
{
	for (auto it = entities->begin(); it != entities->end(); ++it) {

		if ((*it)->getUID() == entity->getUID()) {
			return;	//Entity already stored
		}
	}
	entities->push_back(entity);	//Store entity
}

System::GUI::GUI()
{

}


void System::GUI::clickAreaTest(std::shared_ptr<Entity> entity)
{
	auto sr = entity->get <Component::SpriteRenderer>();
	auto b = entity->get <Component::Button>();

	GLFWwindow* m_window;
	double x, y;

	b->setPosition();

	/*
	if (x >= xpos && x <= xpos + width &&
		y >= ypos && y <= ypos + height)
	{
		cout << "Button testing \n";
	}
	*/
}

void System::GUI::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	//Iterate through all entities
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if ((*it)->has<Component::Button>()) {
			addEntity((*it), &m_entities);
		}
	}
}

void System::GUI::update(float dt)
{
	double x, y;

	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	//cursorPositionCallback(glfwGetCurrentContext(), x, y);

	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		if ((*it)->has<Component::Transformable>()) {
			auto t = (*it)->get <Component::Transformable>();
			auto b = (*it)->get <Component::Button>();
			auto s = (*it)->get <Component::SpriteRenderer>();
			
			double xpos, ypos, width, height;

			xpos = t->getPosition().x;
			ypos = t->getPosition().y;

			width = t->getScale().x;
			height = t->getScale().y;

			int tt;
			tt = b->getButtonID();

			/// If inside of the buttons
			if (x >= xpos && x <= xpos + width &&
				y >= ypos && y <= ypos + height)
			{
				if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					/// Main menu
					if (tt == 1) /// Start button
					{
						cout << "Start Button\n\n";
						SceneManager::getInstance()->setLoadingScene("Loading.xml");
						SceneManager::getInstance()->changeScene("WorldTest.xml", true);
					}
					if (tt == 2) /// Settings button
					{
						cout << "Settings Button\n\n";
						SceneManager::getInstance()->setLoadingScene("Loading.xml");
						SceneManager::getInstance()->changeScene("Settings.xml", true);
					}
					if (tt == 3) /// Exit button
					{
						cout << "Exit Button\n\n";
						SceneManager::getInstance()->setLoadingScene("Loading.xml");
						SceneManager::getInstance()->changeScene("Exit.xml", true);
					}
					/// World test
					if (tt == 4) /// Main menu button
					{
						cout << "Main Menu Button \n\n";
						SceneManager::getInstance()->setLoadingScene("Loading.xml");
						SceneManager::getInstance()->changeScene("MainMenu.xml", true);
					}
					/// Settings
					if (tt == 5) /// Option - set screen size to 1024, 768.
					{
						glfwSetWindowSize(glfwGetCurrentContext(), 1024, 768);
						glfwSetWindowAspectRatio(glfwGetCurrentContext(), 1, 1.33);
					}

					if (tt == 6) /// Option - set screen size to 800, 600.
					{
						glfwSetWindowSize(glfwGetCurrentContext(), 1280, 800);
						//glfwSetWindowAspectRatio(glfwGetCurrentContext(), 1, 1.33);
						
					}
					/// Exit
					if (tt == 7) /// Exit
					{
						exit(0);
					}
				}
				else
				{
					if (tt == 3 || tt == 7)
					{
						/// Visual effects
						/// Colour manipulation
						s->setColor(vec3(s->getColor().x * 0.99, s->getColor().y * 0.99, s->getColor().z * 0.99));
						/// Size manipulation
						//t->setScale(vec3(t->getScale().x * 0.99, t->getScale().y * 0.99, 0.0));
						//t->setPosition(vec3(t->getPosition().x / 0.998, t->getPosition().y / 0.998, 0.0));
						
					}
					else
					{
						s->setColor(vec3(s->getColor().x / 0.99, s->getColor().y / 0.99, s->getColor().z / 0.99));/// Brightens the button if moused over
					}
				}
			}
			/// If outside of the buttons
			else
			{
				/// Resets the values of the buttons
				if (tt == 1)
				{
					s->setColor(vec3(1.0f, 0.5f, 0.0f));
				}
				if (tt == 2)
				{
					s->setColor(vec3(0.0f, 1.0f, 0.5f));
				}
				if (tt == 3)
				{
					s->setColor(vec3(0.5f, 0.0f, 1.0f));
					t->setScale(vec3(200.0f, 100.0f, 0.0f));
					t->setPosition(vec3(412.0f, 500.0f, 0.0f));
				}
			}
			
		}
	}
	//Remove Destroyed Entities
	removeDestroyed(&m_entities);
}

void System::GUI::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	/*
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		
	}
	*/
}

void System::GUI::removeDestroyed(std::vector<std::shared_ptr<Entity>>* entities)
{
	for (int i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isDestroyed()) {
			entities->erase(entities->begin() + i);
		}
	}
}