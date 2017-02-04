#include <stdafx.h>
#include "MyTimer.h"

MyTimer::MyTimer()
{
	reset();
}

void MyTimer::reset()
{
	m_fStart = glfwGetTime();
}

float MyTimer::getElapsed()
{
	return glfwGetTime() - m_fStart;
}
