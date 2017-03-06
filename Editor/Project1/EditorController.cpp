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
