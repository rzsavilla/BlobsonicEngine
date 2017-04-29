#include "stdafx.h"
#include "Name.h"

Name::Name()
{

}

void Name::setName(const std::string & newName)
{
	m_sName = newName;
}

std::string Name::getName()
{
	return m_sName;
}
