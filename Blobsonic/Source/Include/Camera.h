/**
*	@file Camera.h
*	@class Camera
*	@author Rozen Savilla
*	@brief Camera component
*	Camera component responsible for determing the orienatation, position or a camera it returns a projection and a view matrix.
*/

#pragma once

#include <stdafx.h>
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transformable.h"

namespace Component {
	class Camera: public Component{
	private:
		std::string m_sType;	//!< Camera Type Either "FirstPerson" or "ThirdPerson"
		float m_fFieldOfView;	//!< Field of View degrees
		float m_fNearPlane;		//!< Closest render distance
		float m_fFarPlane;		//!< Furthest render distance
		float m_fAspectRatio;	//!< Aspect Ratio

		float m_fYaw;			//!< X axis rotation
		float m_fPitch;			//!< Y axis rotation
		float m_fRoll;			//!< Z axis rotation

		glm::vec3 m_vPosition;	//!< World position
		glm::vec4 m_vUp;		//!< Camera up vector
		glm::vec4 m_vLookAt;	//!< Camera target lookat

		bool m_bUsePerspective;	//!< Use perspective projection if true else use othorgraphic
		float m_fMoveSpeed;		//!< Camera world movement speed

		bool m_bLocalPosSet;	//!< A local position has been set
		glm::vec3 m_vLocalPos;	//!< Local position in world space

		//Third Person Camera
		std::shared_ptr<Entity> m_LookAtTarget;	//!< If not null camera will lookat this entity
		float m_fReach;			//!< Distance between camera and follow target
		glm::mat4 thirdPerson();	//!< Calculate position/rotation of the camera in order to follow lookAtTarget
		
		bool m_bEnableRotate;	//!< Enable mouse movement to rotate this camera
	public:
		Camera();				//!< Default contructor

		void zoom(float zoom);					//!< Move camera forward based on rotation
		void strafe(float strafe);				//!< Move camera horizontally based on rotation
		void pedestal(float pedestal);			//!< Move camera vertically based on rotation
		void pitch(float pitch);				//!< Pith camera or X axis rotation
		void yaw(float yaw);					//!< Yaw camera or Y axis rotation
		void roll(float roll);					//!< Roll camera or Z axis rotation
		void rotate(float pitch,float yaw);		//!< Apply pitch and yaw rotation

		void translate(glm::vec3 translation);		//!< Translate camera position				
		void translate(float x, float y, float z);	//!< Translate camera position

		void reset();			//!< Reset camera attributes

		/*!
			Set camera projection attributes
			@param FOV Field of View
			@param AspectRatio Aspect Ratio
			@param Near Closest Render Distance or Near Plane
			@param Far Furthest Render Distance or Far Plane
		*/
		void setProjectionAtt(float FOV, float AspectRatio, float Near, float Far);
		void setFOV(float FOV);						//!< Set field of view
		void setAspectRatio(float AspectRatio);		//!< Set aspect aatio
		void setNearPlane(float Near);				//!< Set near plane
		void setFarPlane(float Far);				//!< Set far plane

		/*!
			Set camera orientation
			Determines the cameras pitch , yaw and roll angle.
			@param newOrientation The camera pitch, yaw and roll angle.
		*/
		void setOrientation(glm::vec3 newOrientation);

		/*!
			Set camera orientation
			Determines the cameras pitch , yaw and roll angle.
			@param newOrientation The camera pitch, yaw and roll angle.
		*/
		void setOrientation(float pitch, float yaw, float roll);
		void setPitch(float pitch);						//!< Set camera pitch angle
		void setYaw(float yaw);							//!< Set camera yaw angle
		void setRoll(float roll);						//!< Set camera roll angle in degrees
		void setPosition(glm::vec3 newPosition);		//!< Set camera position
		void setPosition(float x, float y, float z);	//!< Set camera position
		void setMoveSpeed(float speed);					//!< Set Camera movement speed
		void setLocalPosition(glm::vec3 local);			//!< Position relative to transformable

		void setLookAtTarget(std::shared_ptr<Entity> entity);	//!< Set camera lookat target, if set camera will always look at the targets position
		void setReach(float reach);		//Set the distance between the camera and the LookAtTarget

		/*!
			Determines perspective or orthographic projection.
			@param isPerspective Sets camera projection to perspective if true, if false camera uses orthographic perspective
		*/
		void setPerspective(bool isPerspective);

		float getPitch();		//!< Return pitch angle	(X axis rotation)
		float getYaw();			//!< Return yaw angle	(Y axis rotation)
		float getRoll();		//!< Return roll angle	(Z axis rotation)
		glm::vec3 getPosition();	//!< Return Camera position/eye
		glm::vec3 getLocalPos();	//!< Return cameras local position

		float getMoveSpeed();	//!< Return camera movement speed

		glm::mat4 getView();				//!< Return camera view matrix
		glm::mat4 getProjection();			//!< Return projection matrix

		glm::quat getQuatRotation();		//!< Returns quaternion rotation

		glm::vec4 getUp();
		glm::vec4 getLookAt();

		void enableRotation(bool enable);	//!< Allow camera mouse rotation
		bool isRotationEnabled();
	};
}