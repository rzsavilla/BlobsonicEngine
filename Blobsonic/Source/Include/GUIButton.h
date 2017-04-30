/**
*	@file Button.h
*	@class Button
*	@author Max Spencer-Hughes
*	@brief Button component
*	Button component what renders a button to the window using screen space in an orthographic projection
*/

#pragma once

#include "stdafx.h"
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Component 
{
	class Button : public Component
	{
	private:
		glm::vec2 m_vScreenPosition;	//!< Screen position
		glm::vec2 m_vSize;	//!< Buttons size, X ?& Y

		bool isPressed; // If the button has been clicked
	
	public:
		Button(); // Default constructor attributes

		void setPosition(glm::vec2 setPosition);	//!< Translate buttons position				
		void setPosition(float x, float y);			//!< Translate buttons position
		
		void setSize(glm::vec2 setSize);			//!< Set the buttons size				
		void setSize(float x, float y);				//!< Set the buttons size	

		void setClicked(bool click);
	};
}