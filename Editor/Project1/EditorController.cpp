#include "EditorController.h"
#include "EditorData.h"
#include "EditorView.h"
#include "Scene.h"

EditorController::EditorController()
{
	//Read file or create empty editor
	Scene scene_1 = Scene();
	Scene scene_2 = Scene();

	addScene("s_one", scene_1);
	addScene("s_two", scene_2);

	eView = new EditorView(m_vScene);
	eData = new EditorData(m_vScene);
	eView->Init();
}


EditorController::~EditorController()
{
}

void EditorController::addScene(std::string ID, Scene newScene) {
	m_vScene.push_back(std::pair<std::string, Scene>(ID, newScene));
}

Scene* EditorController::getScene(std::string ID) {
	//Look through vector
	for (auto it = m_vScene.begin(); it != m_vScene.end(); ++it) {
		if ((*it).first == ID) {
			return &(*it).second;		//Returns texture pointer
		}
	}
	return NULL;
}