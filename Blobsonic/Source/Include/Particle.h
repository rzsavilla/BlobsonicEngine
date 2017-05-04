#pragma once
#include "Component.h"


namespace Component {
	class Particle : public Component {

	private:
		glm::vec3 position;
		glm::vec3 lookAt;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		std::string file;
		
		bool hasCollisions;
		float mass;
		float minScale;
		float maxScale;

		bool isDead;
		

	public:
		Particle();

		void setPosition(glm::vec3 pos);
		void setLookAt(glm::vec3 lkat);
		void setVelocity(glm::vec3 vel);
		void setAcceleration(glm::vec3 acc);
		void setHasCollisions(bool state);
		void setMass(float m);
		void setMinScale(float minS);
		void setMaxScale(float maxS);
		void setDead(bool state);

		glm::vec3 getPosition();
		glm::vec3 getLookAt();
		glm::vec3 getVelocity();
		glm::vec3 getAcceleration();
		bool getHasCollisions();
		float getMass();
		float getMinScale();
		float getMaxScale();
		bool getDead();
	};
}