#include "stdafx.h"
#include "UniqueID.h"

//Initialize static class variable
int UniqueID::ms_iUIDCounter = 0;

void UniqueID::setUID()
{
	ms_iUIDCounter++;
	m_uiUID = ms_iUIDCounter;
}

int UniqueID::getUID()
{
	return m_uiUID;
}
