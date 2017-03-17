/**
* @class	Material
* @brief	Material to be set onto a model
* Material determines the reflectivity of a model
*/

#pragma once

#include <stdafx.h>

class Material {
private:
	glm::vec3 m_vAmbientReflect;	//!< Ambient light reflectivity;
	glm::vec3 m_vDiffuseReflect;	//!< Diffuse light reflectivity;
	glm::vec3 m_vSpecularReflect;	//!< Specular light reflectivity;
	float m_fShininess;				//!< Specular highlight;
public:
	Material();																//!< Default Constructor
	Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular,float shininess);		//!< Constructor

	void setReflectivity(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular,float shininess);
	void setAmbient(glm::vec3 Ambient);		//!< Set ambient light reflectivity
	void setDiffuse(glm::vec3 Diffuse);		//!< Set diffuse light reflectivity
	void setSpecular(glm::vec3 Specular);	//!< Set specular light reflectivity
	void setAmbient(float Red, float Green, float Blue);	//!< Set ambient light reflectivity
	void setDiffuse(float Red, float Green, float Blue);	//!< Set diffuse light reflectivity
	void setSpecular(float Red, float Green, float Blue);	//!< Set specular light reflectivity
	void setShininess(float shininess);						//!< Returns specular highlight exponent higher value decreases lights spread increases brightness
		
	glm::vec3 getAmbient() ;		//!< Returns ambient light reflectivity
	glm::vec3 getDiffuse() ;		//!< Returns diffuse light reflectivity
	glm::vec3 getSpecular();		//!< Returns specular light reflectivity
	float getShininess();			//!< Retusn specular highlight exponent
};