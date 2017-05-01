#pragma once

#include "Light.h"

namespace Component {
	class Spotlight: public Component, public Light  {
	private:
		glm::vec3 m_vDirection;

		float m_fCutOff;
		float m_fOuterCutoff;
		float m_fConstant;
		float m_fLinear;
		float m_fQuadratic;
	public:
		Spotlight();		//!< Default constructor

		void setDirection(glm::vec3 direction);
		void setCutOff(float cutOff);
		void setOuterCutOff(float outerCutOff);
		void setConstant(float constant);
		void setLinear(float linear);
		void setQuadratic(float quadratic);

		glm::vec3 getDirection();
		float getCutOff();
		float getOuterCutOff();
		float getConstant();
		float getLinear();
		float getQuadratic();
	};
}