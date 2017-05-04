

//Button::Button(){}
/*
void Button::initButton(Mesh* CubeMesh)
{
	m_buttonModel.setMesh(CubeMesh);
	m_buttonModel.setOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	m_buttonModel.setScale(glm::vec3(20.0f, 10.0f, 0.0f));

	

	m_buttonModel.setRotation(15.0f, xAxis);
	m_buttonModel.setRotation(-15.0f, zAxis);
	m_buttonModel.setRotation(45.0f, yAxis);

	//m_vCameraPos = m_Camera.position();
	m_vCameraProj = m_Camera.projection();
	m_Camera.view();
	

	// Button position values
	//x = 20.0f;
	//y = 10.0f;
	//z = -20.0f;

	// Button colour values
	r = 0.0f;
	g = 0.5f;
	b = 0.5f;
};

Button::Button(Mesh* CubeMesh)
{
	printf("Button Here, Hello World!");

	initButton(CubeMesh);
}

Button::~Button()
{

}

void Button::setPosition()
{ // Sets the position of the button
	//buttonPos = vec3(x, y, z);
	//m_buttonModel.setPosition(buttonPos);
}

void Button::setColour()
{ // Set the colour of the button
	buttonColour = vec3(r, g, b); 
	m_ptrShader->setUniform("myColour", buttonColour);
}

void Button::setText()
{ // Set the text on the button
  //Create button text
  //m_ButtonText = std::make_shared<Text>("Click Me!", m_ptrCharacters, 350.0f, 400.0f, glm::vec3(0.0f, 0.0f, 0.0f), 2.0f);
  //m_ButtonText->setShader(m_ptrResources->getShader("text_shader"));
}

void Button::update()
{ // Updates the button
	m_vCameraPos = m_Camera.view();
	//m_vCameraPos = m_Camera.position();
	x = m_vCameraPos[3][0];
	y = m_vCameraPos[3][1];
	z = m_vCameraPos[3][2];
	buttonPos = vec3(x, y, z);
	m_buttonModel.setPosition(buttonPos);

	m_ptrShader->use();

	m_buttonModel.draw();

}

void Button::draw()
{// Drawn the button using OpenGL

	setColour();
	setPosition();
	//update();

	m_ptrShader->use();

	m_buttonModel.draw();
}

void Button::setShader(std::shared_ptr<GLSLProgram> shader)
{
	m_ptrShader = shader;
	m_buttonModel.setShader(m_ptrShader);
}

void Button::setMaterial(Material * material)
{
	m_ptrMaterial = material;
	m_buttonModel.setMaterial(m_ptrMaterial);
}

std::shared_ptr<GLSLProgram> Button::getShader()
{
	return m_buttonModel.getShader();
}

bool Button::collision(glm::vec2 point)
{
	return false;
}

*/
