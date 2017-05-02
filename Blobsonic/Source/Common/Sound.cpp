#include "stdafx.h"
#include "Sound.h"

Component::Sound::Sound()
{
	isPlaying = false;
	isLooping = false;
	startsPaused = false;

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

void Component::Sound::setFile(std::string f)
{
	file = f;
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
