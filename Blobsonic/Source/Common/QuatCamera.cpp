/*!
	Code is from IMAT3111 Shader programming module
*/

#include <stdafx.h>
#include "QuatCamera.h"
#include <cmath>

#define PI 3.141592653589793
#define TWOPI 6.2831853071795862
#define TWOPI_F 6.2831853f
#define TO_RADIANS(x) (x * 0.017453292519943295)
#define TO_DEGREES(x) (x * 57.29577951308232)

#include <iostream>

//World coordinate System Axes
const glm::vec3 WORLDX = glm::vec3(1, 0, 0);
const glm::vec3 WORLDY = glm::vec3(0, 1, 0);
const glm::vec3 WORLDZ = glm::vec3(0, 0, 1);


/////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////////////
QuatCamera::QuatCamera()
{
	reset();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the position
/////////////////////////////////////////////////////////////////////////////////////////////
const glm::vec3& QuatCamera::position() const
{
	return _position;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the position
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::setPosition(const glm::vec3& position)
{
	_position = position;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Get the fieldOfView
/////////////////////////////////////////////////////////////////////////////////////////////
float QuatCamera::fieldOfView() const
{
	return _fieldOfView;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the fieldOfView
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::setFieldOfView(float fieldOfView)
{
	assert(fieldOfView>0.0f && fieldOfView <180.0f);
	_fieldOfView = glm::radians(fieldOfView);
	_projection = glm::perspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the aspectRatio
/////////////////////////////////////////////////////////////////////////////////////////////
float QuatCamera::aspectRatio() const
{
	return _aspectRatio;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the aspectRatio
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::setAspectRatio(float aspectRatio)
{
	assert(aspectRatio >0.0f);
	_aspectRatio = aspectRatio;
	_projection = glm::perspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane);
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Get the nearPlane
/////////////////////////////////////////////////////////////////////////////////////////////
float QuatCamera::nearPlane() const
{
	return _nearPlane;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the far Plane
/////////////////////////////////////////////////////////////////////////////////////////////
float QuatCamera::farPlane() const
{
	return _farPlane;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Set the nearPlane and the farPlane
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::setNearAndFarPlanes(float nearPlane, float farPlane)
{
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	_nearPlane = nearPlane;
	_farPlane = farPlane;
	_projection = glm::perspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Generate a quaternion from axis and rotation angle in radians
//This is to construct the rotation quaternion
////////////////////////////////////////////////////////////////////////////////////////////

//glm::quat fromAxisAngle(glm::vec3 axis, float angle)
//{
//	glm::quat rotation;
//
//	float r = (angle);
//
//	rotation.w = cos(angle / 2);
//	rotation.x = sin(angle / 2) * axis.x;
//	rotation.y = sin(angle / 2) * axis.y;
//	rotation.z = sin(angle / 2) * axis.z;
//	return rotation;
//}

/////////////////////////////////////////////////////////////////////////////////////////////
//Rotate the camera
//Orient according to required pitch and yaw
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::rotate(const float yaw, const float pitch)
{
	/*glm::quat xPitch = fromAxisAngle(WORLDX, pitch/10);
	glm::quat yYaw = fromAxisAngle(WORLDY, yaw/10);

	_orientation = xPitch * _orientation * yYaw;

	_orientation = glm::normalize(_orientation);

	updateView();*/
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Pan the camera
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::pan(const float x, const float y)
{
	//_position += _xaxis * x;
	//_position += _yaxis * -y;

	////Now call update()
	//updateView();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Zoom the camera
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::zoom(const float z)
{
	//_position -= _zaxis * z;
	////Now call updateView()
	//updateView();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update the camera view
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::updateView()
{
	//Construct the view matrix from orientation quaternion and position vector

	//First get the matrix from the 'orientaation' Quaternion
	//This deals with the rotation and scale part of the view matrix
	_view = glm::mat4_cast(_orientation); // Rotation and Scale

	//Extract the camera coordinate axes from this matrix
	_xaxis = glm::vec3(_view[0][0], _view[1][0], _view[2][0]);
	_yaxis = glm::vec3(_view[0][1], _view[1][1], _view[2][1]);
	_zaxis = glm::vec3(_view[0][2], _view[1][2], _view[2][2]);

	if (m_bHasTarget) {
		//_view = glm::lookAt(_position,target,glm::vec3(0.0f,1.0f,0.0f));
		_view = glm::lookAt(glm::vec3(40.0f,40.0f,-40.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else {
		//And use this and current camera position to set the translate part of the view matrix
		_view[3][0] = -glm::dot(_xaxis, _position); //Translation x
		_view[3][1] = -glm::dot(_yaxis, _position); //Translation y
		_view[3][2] = -glm::dot(_zaxis, _position); //Translation z
		m_bHasTarget = false;
	}
	//std::cout << 
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the Up
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::roll(const float z)
{
	/* TO DO */
	/* The middle mouse button is set up to call this method
	in order to roll the camera around its z-axis
	This requires similar processing to the rotate(...) method above
	but, of course, should update the camera 'orientation' with
	a roll
	*/
	//glm::quat zRoll = (fromAxisAngle(WORLDZ, z/10));
	//_orientation = _orientation * zRoll;
	//_orientation = glm::normalize(_orientation);
	//updateView();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the camera
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::reset(void)
{
	//Initialise camera axes
	//_xaxis = WORLDX;
	//_yaxis = WORLDY;
	//_zaxis = WORLDZ;

	////Initialise camera position 
	//_position = glm::vec3(0.0f, 0.0f, 20.0f);

	////Initialise the orientation
	//_orientation = glm::quat(1.0, 0.0, 0.0, 0.0);

	////Initialise camera perspective parameters
	//_fieldOfView = glm::radians(50.0f);
	//_nearPlane = 0.01f;
	//_farPlane = 1000.0f;
	//_aspectRatio = 4.0f / 3.0f;

	//_projection = glm::perspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane);

	//updateView();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera View matrix
/////////////////////////////////////////////////////////////////////////////////////////////
glm::mat4 QuatCamera::view()
{
	//this->updateView();
	return _view;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera Projection matrix
/////////////////////////////////////////////////////////////////////////////////////////////
glm::mat4 QuatCamera::projection()
{
	return _projection;
}

void QuatCamera::lookAt(glm::vec3 pos)
{
	target = pos;
	m_bHasTarget = true;
}

void QuatCamera::setRotateSpeed(float newSpeed)
{
	_rotateSpeed = newSpeed;
}

void QuatCamera::setMoveSpeed(float newSpeed)
{
	_moveSpeed = newSpeed;
}


float QuatCamera::getRotateSpeed()
{
	return _rotateSpeed;
}

float QuatCamera::getMoveSpeed()
{
	return _moveSpeed;
}
