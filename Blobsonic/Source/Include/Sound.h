#pragma once


#include "Component.h"

namespace Component {
	class Sound : public Component {

	private:
		std::string file;
		bool isPlaying;
		bool isLooping;
		bool startsPaused;

	public:
		Sound(std::string f, bool playing, bool looping, bool paused);

		std::string getFile();
		bool getPlaying();
		bool getLooping();
		bool getPaused();

		void setPlaying(bool state);
		void setLooping(bool state);
		void setPaused(bool state);
	};
}