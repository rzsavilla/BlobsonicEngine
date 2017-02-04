#include <stdafx.h>
#include "MyRobot.h"

void MyRobot::initModel(Mesh* CubeMesh)
{
	//Load Cube mesh
	Head.setMesh(CubeMesh);
	Torso.setMesh(CubeMesh);
	ArmLeft.setMesh(CubeMesh);
	ArmRight.setMesh(CubeMesh);
	LegLeft.setMesh(CubeMesh);
	LegRight.setMesh(CubeMesh);
	FootLeft.setMesh(CubeMesh);
	FootRight.setMesh(CubeMesh);

	Head.setOrigin(glm::vec3(0.0f, 3.5f, 0.0f));
	Torso.setOrigin(glm::vec3(0.0f, +0.0f, 0.0f));
	ArmLeft.setOrigin(glm::vec3(-2.0f, -2.0f, 0.0f));	//Flipped
	ArmRight.setOrigin(glm::vec3(2.0f, -2.0f, 0.0f));
	LegLeft.setOrigin(glm::vec3(1.0f, -6.0f, 0.0f));
	LegRight.setOrigin(glm::vec3(-1.0f, -6.0f, 0.0f));
	FootLeft.setOrigin(glm::vec3(1.0f, -9.0f, 1.0f));
	FootRight.setOrigin(glm::vec3(-1.0f, -9.0f, 1.0f));

	//Scale robot parts
	Head.setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	Torso.setScale(glm::vec3(3.0f, 5.0f, 2.0f));
	ArmLeft.setScale(glm::vec3(1.0f, 4.0f, 1.0f));
	ArmRight.setScale(glm::vec3(1.0f, 4.0f, 1.0f));
	LegLeft.setScale(glm::vec3(1.0f, 5.0f, 1.0f));
	LegRight.setScale(glm::vec3(1.0f, 5.0f, 1.0f));
	FootLeft.setScale(glm::vec3(1.0f, 0.5f, 3.0f));
	FootRight.setScale(glm::vec3(1.0f, 0.5f, 3.0f));
};

MyRobot::MyRobot(Mesh* CubeMesh)
{
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	m_fRotationY = 0.0f;
	m_fTurnSpeed = 3.0f;
	m_fMoveSpeed = 15.0f;
	m_fAnimationSpeed = 50.0f;

	initModel(CubeMesh);
}

MyRobot::~MyRobot()
{

}

void MyRobot::turnLeft()
{
	m_fRotationY -= m_fTurnSpeed;
}

void MyRobot::turnRight()
{
	m_fRotationY += m_fTurnSpeed;
}

void MyRobot::moveForward()
{
	m_bForwards = true;
}

void MyRobot::moveBackward()
{
	m_bBackwards = true;
}

void MyRobot::setPosition(float x, float y, float z)
{
	m_vPosition = glm::vec3(x, y, z);
}

void MyRobot::setMoveSpeed(float newSpeed)
{
	m_fMoveSpeed = newSpeed;
}

void MyRobot::setTurnSpeed(float newTurnSpeed)
{
	m_fTurnSpeed = newTurnSpeed;
}

glm::vec3 MyRobot::getPosition()
{
	return m_vPosition;
}

void MyRobot::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_ptrShader = shader;
	Head.setShader(m_ptrShader);
	Torso.setShader(m_ptrShader);
	ArmLeft.setShader(m_ptrShader);
	ArmRight.setShader(m_ptrShader);
	LegLeft.setShader(m_ptrShader);
	LegRight.setShader(m_ptrShader);
	FootLeft.setShader(m_ptrShader);
	FootRight.setShader(m_ptrShader);
}

void MyRobot::setMaterial(Material * material)
{
	m_ptrMaterial = material;
	Head.setMaterial(m_ptrMaterial);
	Torso.setMaterial(m_ptrMaterial);
	ArmLeft.setMaterial(m_ptrMaterial);
	ArmRight.setMaterial(m_ptrMaterial);
	LegLeft.setMaterial(m_ptrMaterial);
	LegRight.setMaterial(m_ptrMaterial);
	FootLeft.setMaterial(m_ptrMaterial);
	FootRight.setMaterial(m_ptrMaterial);
}

std::shared_ptr<GLSLProgram> MyRobot::getShader()
{
	return Head.getShader();
}

void MyRobot::update(const float dt)
{
	//Set Velocity
	if (m_bForwards) { m_Velocity = glm::vec3(m_fMoveSpeed, m_fMoveSpeed, m_fMoveSpeed); }
	else if (m_bBackwards) { m_Velocity = glm::vec3(-m_fMoveSpeed, -m_fMoveSpeed, -m_fMoveSpeed); }

	//Calculate direction/facing/heading vector
	glm::vec4 forward(1.0f,0.0f,1.0f,1.0f);
	//Calculate robots rotation
	float rad = glm::radians(m_fRotationY + 45.0f);
	glm::mat4 orientation(
		cos(rad), 0.0f, sin(rad), 0.0f,
		0, 1.0, 0.0f, 0.0f,
		-sin(rad), 0.0f, cos(rad), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	forward = orientation * forward;		//Forward vector
	forward = glm::normalize(forward);		//Heading/Direction vector
	m_Velocity = m_Velocity * glm::vec3(forward.x, forward.y, forward.z) ;	//Apply velocity/speed

	m_vPosition += m_Velocity * dt;	//Integrate

	//Animate robot
	if (m_bForwards || m_bBackwards) {
		animate(dt);
	}

	//Reset action flags
	m_bBackwards = false;
	m_bForwards = false;
	m_bAnimate = false;
}

void MyRobot::draw()
{
	//m_fRotationY += 0.1f;
	glm::vec3 pos = m_vPosition;
	//Move
	Head.setPosition(pos);
	Torso.setPosition(pos);
	FootLeft.setPosition(pos);
	FootRight.setPosition(pos);
	ArmLeft.setPosition(pos);
	ArmRight.setPosition(pos);
	LegLeft.setPosition(pos);
	LegRight.setPosition(pos);

	//Reset rotations;
	Head.setRotation(0.0f, Axis::xAxis);
	Torso.setRotation(0.0f, Axis::xAxis);
	FootLeft.setRotation(0.0f, Axis::xAxis);
	FootRight.setRotation(0.0f, Axis::xAxis);
	ArmLeft.setRotation(0.0f, Axis::xAxis);
	ArmRight.setRotation(0.0f, Axis::xAxis);
	LegLeft.setRotation(0.0f, Axis::xAxis);
	LegRight.setRotation(0.0f, Axis::xAxis);
	FootLeft.setRotation(0.0f, Axis::yAxis);
	FootRight.setRotation(0.0f, Axis::yAxis);

	//Rotate entire model to face orientation
	Head.rotate(m_fRotationY, Axis::yAxis);
	Torso.rotate(m_fRotationY, Axis::yAxis);
	ArmLeft.rotate(m_fRotationY, Axis::yAxis);;
	ArmRight.rotate(m_fRotationY, Axis::yAxis);;
	LegLeft.setRotation(m_fRotationY, Axis::yAxis);
	LegRight.setRotation(m_fRotationY, Axis::yAxis);
	FootLeft.setRotation(m_fRotationY, Axis::yAxis);
	FootRight.setRotation(m_fRotationY, Axis::yAxis);

	ArmLeft.translate(glm::vec3(0.0f, 2.0f, 0.0f));
	ArmLeft.rotate(armAngles[LEFT], Axis::xAxis);

	ArmRight.translate(glm::vec3(0.0f, 2.0f, 0.0f));
	ArmRight.rotate(armAngles[RIGHT], Axis::xAxis);

	LegLeft.translate(glm::vec3(0.0f, 0.5f, -0.5f));
	LegLeft.rotate(legAngles[LEFT], Axis::xAxis);
	LegRight.translate(glm::vec3(0.0f, 0.5f, -0.5f));
	LegRight.rotate(legAngles[RIGHT], Axis::xAxis);

	FootLeft.translate(glm::vec3(0.0f, 0.5f, -0.5f));
	FootLeft.rotate(legAngles[LEFT], Axis::xAxis);
	FootRight.translate(glm::vec3(0.0f, 0.5f, -0.5f));
	FootRight.rotate(legAngles[RIGHT], Axis::xAxis);
	
	LegLeft.translate(glm::vec3(-0.0f, -0.5f, -0.0f));

	//////////Draw///////
	m_ptrShader->use();
	m_ptrShader->setUniform("myColour", glm::vec3(1.0f,1.0f,1.0f));		//White
	Head.draw();
	FootLeft.draw();
	FootRight.draw();
	m_ptrShader->setUniform("myColour", glm::vec3(0.0f, 0.0f, 1.0f));	//Blue
	Torso.draw();
	m_ptrShader->setUniform("myColour", glm::vec3(1.0f, 0.0f, 0.0f));	//Red
	ArmLeft.draw();
	ArmRight.draw();
	m_ptrShader->setUniform("myColour", glm::vec3(1.0f, 1.0f, 0.0f));	//Yellow
	LegLeft.draw();
	LegRight.draw();
}

void MyRobot::animate(float dt)
{
	// if leg is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{
		// arms
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += m_fAnimationSpeed * dt;
		else
			armAngles[side] -= m_fAnimationSpeed * dt;

		// change state if exceeding angles
		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = FORWARD_STATE;

		// legs
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += m_fAnimationSpeed * dt;
		else
			legAngles[side] -= m_fAnimationSpeed * dt;

		// change state if exceeding angles
		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = FORWARD_STATE;
	}
}
