/**
* @class	Light
* @brief	Lighting components base class 
* @author	Rozen Savilla
* Base class for light components, stores the lights intensity
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
class Light {
	private:
		glm::vec3 m_vAmbient;	//!< Ambient Light Intensity
		glm::vec3 m_vDiffuse;	//!< Diffuse Light Intensity
		glm::vec3 m_vSpecular;	//!< Specular Light Intensity
	public:
		Light();				//!< Default Constructor
		Light(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);	//!< Constructor

		//! Set ambient, diffuse, specular light intensity.
		void setIntensity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
		void setAmbient(glm::vec3 Ambient);		//!< Set ambient light intensity
		void setDiffuse(glm::vec3 Diffuse);		//!< Set diffuse light intensity
		void setSpecular(glm::vec3 Specular);	//!< Set specular light intensity
		void setAmbient(float Red, float Green, float Blue);	//!< Set ambient light intensity
		void setDiffuse(float Red, float Green, float Blue);	//!< Set diffuse light intensity
		void setSpecular(float Red, float Green, float Blue);	//!< Set specular light intensity

		glm::vec3 getAmbient();		//!< Returns ambient light intensity
		glm::vec3 getDiffuse();		//!< Returns diffuse light intensity
		glm::vec3 getSpecular();	//!< Returns specular light intensitys
	};
}