#include <stdafx.h>
#include "SceneComponent.h"
#include "SceneLoader.h"
#include "Render.h"
#include "Engine.h"

/*
	Text Rendering code
	https://learnopengl.com/#!In-Practice/Text-Rendering
*/

#include <ft2build.h>
#include FT_FREETYPE_H  

//void SceneComponent::handleInput()
//{
//	//m_scenes.at(m_uiActiveScene).second->handleInput(m_ptrWindow);
//}
//
//std::shared_ptr<Text> SceneComponent::getTextObject(std::string id)
//{
//	for (auto it = m_vTexts.begin(); it != m_vTexts.end(); ++it) {
//		if ((*it).first == id) {
//			return (*it).second;
//		}
//	}
//	return NULL;
//}
//
//void SceneComponent::init()
//{
//	//////Initialize OpenGL and create GLFW window
//	if (!m_bWindowLoaded) {
//		// Initialize GLFW
//		if (!glfwInit()) exit(EXIT_FAILURE);
//
//		// Select OpenGL 4.3 with a forward compatible core profile.
//		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
//		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//		glfwWindowHint(GLFW_RESIZABLE, FALSE);
//		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
//		glfwWindowHint(GLFW_DEPTH_BITS, 32);
//
//		//Open window
//		m_ptrWindow = glfwCreateWindow(1024, 768, "Barrel Engine", NULL, NULL);
//		if (m_ptrWindow == NULL) {
//			std::cout << "Failed to load window\n";
//			system("pause");
//			glfwTerminate();
//			exit(EXIT_FAILURE);
//		}
//		glfwMakeContextCurrent(m_ptrWindow);
//
//		//Load OpenGL functions
//		gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
//		if (!didLoad) {
//			//Clean up and abort
//			glfwTerminate();
//			exit(EXIT_FAILURE);
//		}
//
//		m_bWindowLoaded = true;
//		//Pass GLFW window pointer to components
//		//m_ptrLocalMessages->push_back(std::make_shared<SetWindow>(m_ptrWindow));
//
//		//////Freetype /////////
//		/*
//			https://learnopengl.com/#!In-Practice/Text-Rendering
//		*/
//		gl::Enable(gl::BLEND);
//		gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
//
//	}
//
//	// FreeType
//	FT_Library ft;
//	// All functions return a value different than 0 whenever an error occurred
//	if (FT_Init_FreeType(&ft))
//		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//
//	// Load font as face
//	FT_Face face;
//	if (FT_New_Face(ft, "Source/Resources/fonts/arial.ttf", 0, &face))
//		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//
//	// Set size to load glyphs as
//	FT_Set_Pixel_Sizes(face, 0, 48);
//
//	// Disable byte-alignment restriction
//	gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);
//
//	// Load first 128 characters of ASCII set
//	for (GLubyte c = 0; c < 128; c++)
//	{
//		// Load character glyph 
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//		{
//			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//			continue;
//		}
//		// Generate texture
//		GLuint texture;
//		gl::GenTextures(1, &texture);
//		gl::BindTexture(gl::TEXTURE_2D, texture);
//		gl::TexImage2D(
//			gl::TEXTURE_2D,
//			0,
//			gl::RED,
//			face->glyph->bitmap.width,
//			face->glyph->bitmap.rows,
//			0,
//			gl::RED,
//			gl::UNSIGNED_BYTE,
//			face->glyph->bitmap.buffer
//		);
//		// Set texture options
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
//		// Now store character for later use
//		Character character = {
//			texture,
//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			face->glyph->advance.x
//		};
//		m_Characters.insert(std::pair<GLchar, Character>(c, character));
//	}
//	gl::BindTexture(gl::TEXTURE_2D, 0);
//	// Destroy FreeType once finished
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//	
//	//////Load Scenes//////
//	m_uiActiveScene = 0;
//	m_scenes.clear();
//	m_res = ResourceManager();
//	std::string sFile = "Source\\Resources\\scenes\\Physics Test.xml";
//	//SceneLoader sceneLoader(sFile, &m_res, &m_scenes);
//
//	if (m_scenes.empty()) {
//		std::cout << "No scenes loaded\n";
//		system("pause");
//		glfwTerminate();
//		exit(EXIT_FAILURE);
//	}
//
//	//////Initialize loaded scenes//////
//	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
//		(*it).second->setCharacters(&m_Characters);		//Allows scene to create Text
//		(*it).second->setResources(&m_res);				//Access to resources
//		//(*it).second->setMessages(m_ptrLocalMessages);	//Allow scene to create messages for components
//		(*it).second->initScene();
//	}
//	m_bReload = false;
//
//	////////Text//////
//	for (auto it = m_vTexts.begin(); it != m_vTexts.end(); ++it) {
//		//Set shader to all text objects
//		(*it).second->setShader(m_res.getShader("text_shader"));
//	}
//
//	//Create fps text
//	m_FPSText = std::make_shared<Text>("FPS:", &m_Characters, 1.0f, 745, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
//	m_FPSText->setShader(m_res.getShader("text_shader"));
//}
//
//void SceneComponent::handleMessage(std::shared_ptr<Message> msg)
//{
//	if (msg->sID == "Scene_Reload") {
//		std::cout << "\n\nReloading Scene..........\n\n";
//		m_bReload = true;
//	}
//	else if (msg->sID == "Engine_FrameCount") {
//		//int i = static_cast<EngineMessage::FrameCount*>(msg.get())->iFrames;	//get data from message
//		//m_FPSText->setString("FPS:" + std::to_string(i));
//	}
//	else if (msg->sID == "Scene_Game") {
//		//Look for game scene index
//		for (int i = 0; i < m_scenes.size(); i++) {
//			if (m_scenes.at(i).first == "game_scene") {
//				m_uiActiveScene = i;	//Set active scene
//				return;
//			}
//		}
//	}
//}
//
//void SceneComponent::update(float dt)
//{
//	//Handle Inputs for active scene
//	handleInput();
//
//	//Create draw message for render component
//	if (!m_bReload) {
//		//Update active scene
//		//m_scenes.at(m_uiActiveScene).second->update(dt);
//		//Draw message for active scene
//		//m_ptrLocalMessages->push_back(std::make_shared<RenderComponent::Draw>(m_scenes.at(m_uiActiveScene).second));
//		//Draw message for texts
//		for (auto it = m_vTexts.begin(); it != m_vTexts.end(); ++it) {
//			//m_ptrLocalMessages->push_back(std::make_shared<RenderComponent::Draw>((*it).second));
//		}
//		//m_ptrLocalMessages->push_back(std::make_shared<RenderComponent::Draw>(m_FPSText));
//	}
//	else {
//		init();	//Reload scenes
//	}
//}