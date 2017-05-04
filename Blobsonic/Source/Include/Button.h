#pragma once

#include <GLSLProgram.h>
#include "Component.h"

namespace Component
{
	class Button : public Component
	{
	private:
		bool m_bIsClicked;
		int m_iButtonID;
		double xPos, yPos;

		GLFWwindow* m_window;

	public:
		Button();
		bool getIsClicked();
		int getButtonID();
		double getXPos();
		double getYPos();

		void setIsClicked(bool click);
		void setButtonID(int ID);
		void setPosition();
	};
}