#include <stdafx.h>
#include <ID.h>

void ID::setID(std::string newID)
{
	m_sID = newID;
}

std::string ID::getID()
{
	return m_sID;
}
