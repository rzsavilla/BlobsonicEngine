
#ifndef PHYSCIAL_H
#define PHYSCIAL_H


//Chris O'Neill



class Physical : public Component::Component
{
private:
	bool m_bEnableGravitiy;
public:
	
	Physical(); // <! Default Contructor for physical Object

	float m_fMass; //<! Mass of object in kg's
	float m_fINVMass; //<! inverse mass Mass of object in kg's
	float m_fRestitution; // <! Collision restitution

	glm::vec3 m_fForce;	//<! Force of object in newtons
	glm::vec3 m_vVelocity; //<! Vel of object in m/s
	glm::vec3 m_vAcceleration; //<! Accel of object in m/s/s

	void setMass(float newMass);				//!< set Mass in kg
	void setfINVMass(float newINVMass);			//!< set inverse Mass in kg
	void setRestitution(float newRestitution);	//!< set collision restitution
	
	void setForce(glm::vec3 newFoce);			//!< Set value of force being appplied
	void applyForce(glm::vec3 appliedForce);	//!< Add to current force being applied 
	void setVelocity(glm::vec3 velocity);		//!< Set current velocity

	float getMass();			//!< Return mass in kg
	float getINVMass();			//!< Return inverse mass in kg
	float getRestitition();		//!< Return collision restitution

	glm::vec3 getForce();		//!< returns current force being applied
	glm::vec3 getVelocity();	//!< return current velocity
	glm::vec3 getAcceleration();	//!< return current acceleration m/s/s
	void applyImpulse(glm::vec3 Normal, float force);

};



#endif // !PHYSCIAL_H
