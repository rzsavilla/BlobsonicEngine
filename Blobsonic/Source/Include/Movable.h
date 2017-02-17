#pragma once

#include "ObjectComponent.h"


namespace M_Movable {
	struct SetVel: public Message {
		SetVel(glm::vec3 v) {
			sID = "Movable_SetVel";
			newVelocity = v;
		}
		glm::vec3 newVelocity;
	};
}

namespace OC {
	class Movable : public OC::ObjectComponent {
	private:
		glm::vec3 m_vVelocity;
	public:
		Movable();

		void handleMessage(std::shared_ptr<Message> msg);

		void update(float dt);
	};
}