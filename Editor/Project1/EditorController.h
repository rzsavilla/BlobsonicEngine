#include "Scene.h"

#pragma once
class EditorView;
class EditorData;

class EditorController
{
private:
	std::vector<std::pair<std::string, Scene>> m_vScene;

public:
	EditorController();
	~EditorController();
	EditorView* eView;
	EditorData* eData;

	void addScene(std::string ID, Scene newScene);
	Scene* getScene(std::string ID);

};

