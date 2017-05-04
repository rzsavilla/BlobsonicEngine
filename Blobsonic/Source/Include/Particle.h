#pragma once
#include "Component.h"
#include "AssimpMesh.h"
#include "Material.h"
#include "Texture.h"
#include "GLSLProgram.h"


namespace Component {
	class Particle : public Component {

	private:

		glm::vec3 relPosition;
		glm::vec3 lookAt;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		std::string file;
		std::shared_ptr<AssimpMesh> m_particleMesh;
		std::shared_ptr<Material> m_material;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<GLSLProgram> m_shader;

		bool hasCollisions;
		float mass;
		float minScale;
		float maxScale;
		float numParticles;

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
		void setNumMax(float numM);
		void setDead(bool state);
		void setMesh(std::shared_ptr<AssimpMesh> mesh);
		void setShader(std::shared_ptr<GLSLProgram> shad);
		void setTexture(std::shared_ptr<Texture> tex);
		void setMaterial(std::shared_ptr<Material> mat);

		glm::vec3 getPosition();
		glm::vec3 getLookAt();
		glm::vec3 getVelocity();
		glm::vec3 getAcceleration();
		bool getHasCollisions();
		float getMass();
		float getMinScale();
		float getMaxScale();
		float getNumMax();
		bool getDead();
		std::shared_ptr<AssimpMesh> getMesh();
		std::shared_ptr<GLSLProgram> getShader();
		std::shared_ptr<Texture> getTexture();
		std::shared_ptr<Material> getMaterial();
	};
}