#pragma once

#include "Message.h"

#include "Entity.h"

namespace SceneMessage {
	//!< Adds entity to current scene
	struct AddEntity : public Message {
		AddEntity(std::shared_ptr<Entity> newEntity):
			entity(newEntity)
		{
			sID = "AddEntity";
		}
		std::shared_ptr<Entity> entity;
	};

	struct DestroyEntity : public Message {
		DestroyEntity(unsigned int id):
			ID(id)
		{
			sID = "DestroyEntity";
		}
		unsigned int ID;
	};

	struct Reload : public Message {
		Reload() { sID = "Scene_Reload"; }
	};

	struct Exit : public Message {
		Exit() { sID = "Scene_Exit"; }
	};

	struct SceneChanged : public Message {
		SceneChanged() { sID = "SceneChanged"; }
	};

	struct ChangeScene :public Message {
		ChangeScene(std::string NewScene) {
			sID = "ChangeScene";
			sNewScene = NewScene;
		}
		std::string sNewScene;
	};

	//! Report to sytems to create a collision message for this entity
	struct ListenToCollision : public Message {
		ListenToCollision(unsigned int entityID) {
			sID = "ListenToCollision";
		}
		unsigned int entityID;
	};

	//! Message to report that a collision has occured between two entities
	struct CollisionReport : public Message {
		CollisionReport(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2):
			entity1(entity1),
			entity2(entity2)
		{
			sID = "CollisionReport";
		}
		const std::shared_ptr<Entity> entity1;
		const std::shared_ptr<Entity> entity2;
	};
}