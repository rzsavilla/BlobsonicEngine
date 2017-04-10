/**
* @class	MyRobot
* @brief	Animated Robot
* Coloured animated robot based on Robot example
*/

#pragma once

#include <stdafx.h>
#include "ModelOLD.h"

// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

class MyRobot
{
private:
	char legStates[2];
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	Model Head, Torso, ArmLeft, ArmRight, LegLeft, LegRight, FootLeft, FootRight;
	void initModel(Mesh* CubeMesh);	//!< Initial robot with mesh to draw its body parts

	bool m_bForwards;			//!< Flag to move robot forwards
	bool m_bBackwards;			//!< Flag to move robot backwards
	bool m_bAnimate;			//!< Flag to animate robot

	glm::vec3 m_vPosition;		//!< Currrent Position
	glm::vec3 m_vDirection;		//!< Direction vector
	float m_fRotationY;			//!< Heading/Facing/Orientation
	float m_fTurnSpeed;			//!< How quickly the robot can turn
	float m_fMoveSpeed;			//!< How quickly the robot moves towards its heading
	float m_fAnimationSpeed;	//!< Animation speed

	glm::vec3 m_Velocity;			//!< Robots current velocity

	std::shared_ptr<GLSLProgram> m_ptrShader;	//!< Pointer to shader

	Material* m_ptrMaterial;	//!< Pointer to material

	// updates the robot data
	void animate(float dt);		//!< Update robots animation
public:
	MyRobot(Mesh* CubeMesh); //!< Default Constructor
	virtual ~MyRobot();		 //!< Destructor

	void turnLeft();		//!< Rotates robot to the left
	void turnRight();		//!< Rotates robot to the right
	void moveForward();		//!< Moves robot towards facing
	void moveBackward();	//!< Moves robot back

	void setPosition(float x, float y, float z);	//!< Set robots position 
	void setMoveSpeed(float newSpeed);				//!< Set robots movement speed
	void setTurnSpeed(float newTurnSpeed);			//!< Set robots rotation speed

	glm::vec3 getPosition();						//!< Return robots position

	void setShader(std::shared_ptr<GLSLProgram> shader);	//!< Set pointer to shader
	void setMaterial(Material* material);					//!< Set pointer to material

	std::shared_ptr<GLSLProgram> getShader();				//!< Return shader

	void update(const float dt);							//!< Update robot

	void draw();			//!< Render robot

	
};
