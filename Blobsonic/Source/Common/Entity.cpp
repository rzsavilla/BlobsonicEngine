#include "stdafx.h"
#include "Entity.h"


#include "CollisionReporter.h"

Entity::Entity()
{
	this->setUID();
	if (m_bDebug) std::cout << "Entity Created: " << this->getUID() << "\n";
	//CollisionReporter::getInstance()->attachReceiver(this);
}

Entity::~Entity()
{
	m_components.clear();	//Remove all attached components
}
