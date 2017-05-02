#pragma once

#include "Component.h"

//Audio engine
#include <irrKlang\irrKlang.h>
using namespace irrklang;

namespace Component {
	class Sound : public Component {

	private:
		std::string file;
		bool isInitialized;
		bool isPlaying;
		bool isLooping;
		bool startsPaused;
		bool isFinished;
		irrklang::ISound* snd;
		vec3df position;
		bool sound3D;

	public:
		Sound();

		std::string getFile();
		vec3df getPos();
		bool getInitialized();
		bool getPlaying();
		bool getLooping();
		bool getPaused();
		bool getFinished();
		irrklang::ISound* getSound();

		void setFile(std::string f);
		void setInitialized(bool state);
		void setPlaying(bool state);

		void startPlaying2D(ISoundEngine* engine);
		void startPlaying3D(ISoundEngine* engine);
		void stopPlaying(ISoundEngine* engine);
		void setPause();

		void setSoundEmitterPosition(vec3df pos);
		void setSoundListenerPosition(ISoundEngine* engine, vec3df pos, vec3df lookDirection, vec3df velPerSecond, vec3df upVector);

		void setPos(vec3df pos);
		void setLooping(bool state);
		void setPaused(bool state);

		bool getsound3D();

		void setSound3D(bool state);
	};
}