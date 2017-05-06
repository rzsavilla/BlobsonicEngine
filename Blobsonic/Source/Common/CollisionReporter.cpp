#include "stdafx.h"
#include "CollisionReporter.h"
#include "SceneMessages.h"

CollisionReporter::CollisionReporter()
{
}

std::shared_ptr<CollisionReporter> CollisionReporter::getInstance()
{
	static std::shared_ptr<CollisionReporter> instance = nullptr;

	if (!instance)
	{
		if (!instance) {
			instance.reset(new CollisionReporter());
		}
	}
	return instance;
}

CollisionReporter::~CollisionReporter()
{
}

void CollisionReporter::attachReceiver(CollisionReceiver * receiver)
{
	m_vReceivers.push_back(receiver);
}

void CollisionReporter::dettachReceiver(CollisionReceiver * receiver)
{
	for (int i = m_vReceivers.size() - 1; i >= 0; i++) {
		if (m_vReceivers.at(i)->getUID() == receiver->getUID()) {
			//Remove receiver
			m_vReceivers.erase(m_vReceivers.begin() + i);
		}
	}
}

void CollisionReporter::notify(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
	//Remove destroyed
	for (int i = m_vReceivers.size() - 1; i >= 0; i--) {
		if (!m_vReceivers.at(i)) m_vReceivers.erase(m_vReceivers.begin() + i);
	}
	//Notify all listeners that a collision between these two entities has occured
	for (auto it = m_vReceivers.begin(); it != m_vReceivers.end(); ++it) {
		if ((*it)) {
			(*it)->registerCollision(entity1, entity2);
		}
	}
}
