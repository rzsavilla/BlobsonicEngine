/**
* @class	Render
* @brief	Render component draws drawable objects.
* Will draw all objects/draw messages passed to it.
*/

#pragma once

#include <stdafx.h>
#include "Component.h"
#include "Drawable.h"
#include "Light.h"

class Render: public Component {
private:
	GLFWwindow* m_ptrWindow;
	//std::vector<std::pair<std::shared_ptr<GLSLProgram>, std::shared_ptr<Drawable>>> m_ptrDrawObjects;	//Stores pointers for objects that need to be drawn along with shader to be used
	std::vector<std::shared_ptr<Drawable>> m_ptrDrawObjects;	//Stores pointers for objects that need to be drawn along with shader to be used
	QuatCamera* m_ptrCamera;											//Pointer to camera in use
	std::vector<std::pair<std::string, Light>>* m_ptrLights;			//Pointer to vector of lights
public:
	Render();	//!< Default constructor

	//! Set pointer for window to draw onto
	void setWindow(GLFWwindow* ptr);

	void init();										//!< Initialize render component
	void handleMessage(std::shared_ptr<Message> msg);	//!< Handle messages received by component
	void update(float dt);								//!< Update render component. Will draw drawable objects
};

//Messages for communicating with Render Component
namespace RenderComponent {
	//Message for render component to draw object
	struct Draw : public Message {
		Draw(std::shared_ptr<Drawable> obj)
			:drawObj(obj)
		{
			sID = "Render_Draw";
		}
		std::shared_ptr<Drawable> drawObj;		//Object to be drawn
	};
}
