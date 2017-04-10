#pragma once

#include "Message.h"

namespace SceneMessage {
	struct SceneSplash : public Message {
		SceneSplash() { sID = "Scene_Splash"; }
	};

	struct StartScene : public Message {
		StartScene() { sID = "Scene_Start"; }
	};

	struct GameScene : public Message {
		GameScene() { sID = "Scene_Game"; }
	};

	struct Reload : public Message {
		Reload() { sID = "Scene_Reload"; }
	};

	struct Exit : public Message {
		Exit() { sID = "Scene_Exit"; }
	};
}