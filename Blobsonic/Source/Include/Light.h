/**
* @class	Light
* @brief	Light stores light properties
* Store light parameters to be passed to a shader program
*/

#pragma once

#include <stdafx.h>

class Light {
private:
	glm::vec3 m_vPosition;	//!< Position of the light;

	glm::vec3 m_vAmbient;	//!< Ambient Light Intensity
	glm::vec3 m_vDiffuse;	//!< Diffuse Light Intensity
	glm::vec3 m_vSpecular;	//!< Specular Light Intensity
	float m_fRadius;		//!< Radius of the light
public:
	Light();															//!< Default Constructor
	Light(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float radius);	//!< Constructor

	void setPosition(glm::vec3 position);
	void setPosition(float x, float y, float z);

	void setIntensity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float radius);
	void setAmbient(glm::vec3 Ambient);		//!< Set ambient light intensity
	void setDiffuse(glm::vec3 Diffuse);		//!< Set diffuse light intensity
	void setSpecular(glm::vec3 Specular);	//!< Set specular light intensity
	void setAmbient(float Red, float Green, float Blue);	//!< Set ambient light intensity
	void setDiffuse(float Red, float Green, float Blue);	//!< Set diffuse light intensity
	void setSpecula(float Red, float Green, float Blue);	//!< Set specular light intensity
	void setRadius(float radius);							//!< Set light radius

	glm::vec3 getPosition();	//!< Returns light position;

	glm::vec3 getAmbient();		//!< Returns ambient light intensity
	glm::vec3 getDiffuse();		//!< Returns diffuse light intensity
	glm::vec3 getSpecular();	//!< Returns specular light intensitys
	float getRadius();			//!< Returns lights radius
};