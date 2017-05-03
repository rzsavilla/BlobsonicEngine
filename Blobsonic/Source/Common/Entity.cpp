#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	this->setUID();
	if (m_bDebug) std::cout << "Entity Created: " << this->getUID() << "\n";
}

Entity::~Entity()
{
	m_components.clear();	//Remove all attached components
}
