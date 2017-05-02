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

	public:
		Sound();

		std::string getFile();
		bool getInitialized();
		bool getPlaying();
		bool getLooping();
		bool getPaused();
		bool getFinished();

		void setFile(std::string f);
		void setInitialized(bool state);
		void setPlaying(bool state);

		void startPlaying(ISoundEngine* engine);
		void stopPlaying(ISoundEngine* engine);
		void setPause();

		void setLooping(bool state);
		void setPaused(bool state);
	};
}