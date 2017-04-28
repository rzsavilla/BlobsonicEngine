#include "stdafx.h"
#include "Sound.h"

Component::Sound::Sound(std::string f, bool playing, bool looping, bool paused)
{
	file = f;
	isPlaying = playing;
	isLooping = looping;
	startsPaused = paused;

}

std::string Component::Sound::getFile()
{
	return file;
}

bool Component::Sound::getPlaying()
{
	return isPlaying;
}

bool Component::Sound::getLooping()
{
	return isLooping;
}

bool Component::Sound::getPaused()
{
	return startsPaused;
}

void Component::Sound::setPlaying(bool state)
{
	isPlaying = state;
}

void Component::Sound::setLooping(bool state)
{
	isLooping = state;
}

void Component::Sound::setPaused(bool state)
{
	startsPaused = state;
}
;
