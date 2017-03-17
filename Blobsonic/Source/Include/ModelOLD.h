/**
* @class	Model
* @brief	A drawable game object
* Model is an object that draws and positions a mesh
*/

#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "QuatCamera.h"
#include "Texture.h"
#include "GLSLProgram.h"
#include "Drawable.h"
#include "Transformable.h"

/* http://learnopengl.com/#!Model-Loading/Mesh */

enum Axis { xAxis, yAxis, zAxis };		//!< Axis of rotation

class Model: public Drawable {
private:
	//Render Data
	GLuint VAO, VBO[2], EBO;

	GLuint handle[3];	//!< VBOs

	glm::vec3 m_vPosition;	//!< Model position
	glm::vec3 m_vScale;		//!< Model scale
	glm::vec3 m_vOrigin;	//!< Model origin

	glm::mat4 t, r, s;	//Translation,rotation and scale matrix;

	std::shared_ptr<GLSLProgram> m_ptrShader;	//!< Pointer to shader
	
	Mesh* m_ptrMesh;			//!< Store points to mesh model data
	Texture* m_ptrTexture;		//!< Points to texture
	Material* m_ptrMaterial;	//!< Pointer to model material

	void setBuffers(); //!< Pass mesh data to OpenGL buffers
public:
	Model();									/*!< Default Constructor */

	void setMesh(Mesh * newMesh,Texture* newTexture = NULL);	//!< Set mesh pointer
	void setMaterial(Material* material);						//!< Set material pointer
	void setTexture(Texture* texture);							//!< Set texture pointer
	void setShader(std::shared_ptr<GLSLProgram> shader);		//!< Set shader pointer
	
	void setPosition(glm::vec3 newPos);			/*!< Set model position */
	void setScale(glm::vec3 newScale);			/*!< Set model scale */
	void setRotation(float degrees, Axis axis); /*!< Set model rotation on choosen axis */
	void setOrigin(glm::vec3 newOrigin);		/*!< Set models origin*/

	glm::vec3 getPosition();					//!< Returns models position
	glm::vec3 getScale();
	glm::mat4 getTransform();					//!< Returns model transformation matrix ;


	std::shared_ptr<GLSLProgram> getShader();	//!< Returns pointer to shader

	void translate(glm::vec3 translate);		/*!< Move model */
	void rotate(float degrees, Axis Axis);		/*!< Rotate model */
	void draw();				/*!< Draw model */
};