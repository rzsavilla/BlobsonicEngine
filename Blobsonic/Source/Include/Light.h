/**
* @class	Light
* @brief	Light stores light properties
* @author	Rozen Savilla
* Store light parameters to be passed to a shader program
*/

#pragma once

#include "stdafx.h"
#include "Component.h"

enum LightType {
	Directional,
	Point,
	Spotlight,
};

namespace Component {
class Light: public Component {
	private:
		LightType m_type;		//!< Type of light
		glm::vec3 m_vAmbient;	//!< Ambient Light Intensity
		glm::vec3 m_vDiffuse;	//!< Diffuse Light Intensity
		glm::vec3 m_vSpecular;	//!< Specular Light Intensity
		glm::vec3 m_vDirection;	//!< Light direction
		float m_fRadius;		//!< Radius of the light
	public:
		Light();				//!< Default Constructor
		Light(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float radius);	//!< Constructor

		void setType(LightType type);	//!< Set type of light to be rendered

		//! Set ambient, diffuse, specular light intensity.
		void setIntensity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float radius);
		void setAmbient(glm::vec3 Ambient);		//!< Set ambient light intensity
		void setDiffuse(glm::vec3 Diffuse);		//!< Set diffuse light intensity
		void setSpecular(glm::vec3 Specular);	//!< Set specular light intensity
		void setAmbient(float Red, float Green, float Blue);	//!< Set ambient light intensity
		void setDiffuse(float Red, float Green, float Blue);	//!< Set diffuse light intensity
		void setSpecula(float Red, float Green, float Blue);	//!< Set specular light intensity
		
		void setRadius(float radius);							//!< Set light radius
		void setDirection(glm::vec3 newDirection);				//!< Set Light Direction

		LightType getType();		//!< Return type of light to be rendered
		glm::vec3 getAmbient();		//!< Returns ambient light intensity
		glm::vec3 getDiffuse();		//!< Returns diffuse light intensity
		glm::vec3 getSpecular();	//!< Returns specular light intensitys
		
		float getRadius();			//!< Returns lights radius
		glm::vec3 getDirection();	//!< Returnlight direction
	};
}