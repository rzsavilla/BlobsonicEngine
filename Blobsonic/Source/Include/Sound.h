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
		bool hasVolume;
		bool hasMinDist;

		irrklang::ISound* snd;
		vec3df position;
		bool sound3D;
		float volume;
		float minDist;

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
		float getVolume();
		float getMinDist();
		bool getHasVolume();
		bool getHasMinDist();

		void setFile(std::string f);
		void setInitialized(bool state);
		void setPlaying(bool state);
		void setVolume(float vol);
		void setMinDist(float dist);

		void startPlaying2D(ISoundEngine* engine);
		void startPlaying3D(ISoundEngine* engine);
		void stopPlaying(ISoundEngine* engine);
		void setPause();

		void setSoundEmitterPosition(vec3df pos);
		

		void setPos(vec3df pos);
		void setLooping(bool state);
		void setPaused(bool state);

		bool getsound3D();

		void setSound3D(bool state);
	};
}