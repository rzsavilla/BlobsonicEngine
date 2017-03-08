#include "EditorController.h"
#include "EditorData.h"
#include "EditorView.h"

EditorController::EditorController()
{

	eView = new EditorView();
	eData = new EditorData();
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