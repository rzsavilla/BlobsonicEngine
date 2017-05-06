#pragma once

#include "CollisionReceiver.h"

class CollisionReporter {
private:
	//---Singleton---
	CollisionReporter();
private:
	//--Observer Pattern--
	std::vector<CollisionReceiver*> m_vReceivers;		//!< Pointer to objects that want to be notified
public:
	static std::shared_ptr<CollisionReporter> getInstance();
	~CollisionReporter();

	void attachReceiver(CollisionReceiver* receiver);
	void dettachReceiver(CollisionReceiver* receiver);
	void notify(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);	//!< Notify all receivers
};