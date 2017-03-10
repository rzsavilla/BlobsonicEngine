#pragma once

#include "Scene.h"
#include "Drawable.h"

class Button : public Drawable {
private:
	glm::vec2 m_vPosition;
	glm::vec3 m_vColour;
	glm::vec3 m_vCameraPos;
	glm::mat4 m_vCameraProj;

	std::string m_sString;
	std::shared_ptr<Text> m_ButtonText;
	std::shared_ptr<GLSLProgram> m_ptrShader;
	Material* m_ptrMaterial;	// Pointer to material
	Model m_buttonModel;
	QuatCamera m_Camera;

	float x, y, z;

public:
	Button(Mesh* CubeMesh); //!< Default Constructor
	virtual ~Button(); // Deconstructor

	void initButton(Mesh* CubeMesh);
	//void handleMouseInput(GLFWwindow* window);	//!< Handle user input

	void setShader(std::shared_ptr<GLSLProgram> shader);
	std::shared_ptr<GLSLProgram> getShader();				//!< Return shader
															//void setShader(std::shared_ptr<GLSLProgram> shader);
	void setMaterial(Material * material);

	void setPosition(glm::vec2 newPos);
	void setColour(glm::vec3 newColour);
	void setText();

	void draw() override;

	bool collision(glm::vec2 point);
};