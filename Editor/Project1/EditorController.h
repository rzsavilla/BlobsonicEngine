
#pragma once
class EditorView;
class EditorData;

class EditorController
{
private:


public:
	EditorController();
	~EditorController();
	EditorView* eView;
	EditorData* eData;
	std::vector<std::pair<std::string, Scene>> m_vScene;
	void addScene(std::string ID, Scene newScene);
	Scene* getScene(std::string ID);

	struct components {

	};
};

