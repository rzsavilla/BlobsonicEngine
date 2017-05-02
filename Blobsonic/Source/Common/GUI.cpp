#include "stdafx.h"
#include "Button.h"
#include "SpriteRender.h"
#include "GUI.h"
#include "Transformable.h"
#include "LuaScripting.h"
//Messages
#include "RenderMessages.h"
#include "CameraMessages.h"

using namespace System::Scripting;

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
			bool m_bBright = false;

			xpos = t->getPosition().x;
			ypos = t->getPosition().y;

			width = t->getScale().x;
			height = t->getScale().y;

			/// If inside of the buttons
			if (x >= xpos && x <= xpos + width &&
				y >= ypos && y <= ypos + height)
			{
				if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					if ((*it)->getUID() == 10)
					{
						cout << "Start Button\n\n";
						string changeScene("TestScene");
					}
					else if ((*it)->getUID() == 14)
					{
						cout << "Settings Button\n\n";
					}
					if ((*it)->getUID() == 18)
					{
						cout << "Exit Button\n\n";
						exit(0);
					}
				}
				else if (m_bBright == false)
				{
					s->setColor(vec3(s->getColor().x / 0.7, s->getColor().y / 0.7, s->getColor().z / 0.7));
					m_bBright = true;
				}
			}
			/// If outside of the buttons
			if (x >=! xpos && x <=! xpos + width &&
				y >=! ypos && y <=! ypos + height)
			{
				
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