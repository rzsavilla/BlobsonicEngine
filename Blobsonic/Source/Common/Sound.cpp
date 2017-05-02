#include "stdafx.h"
#include "Sound.h"

//Audio engine
#include <irrKlang\irrKlang.h>

// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <conio.h>
#endif

using namespace irrklang;
Component::Sound::Sound()
{
	isInitialized = false;
	isPlaying = false;
	isLooping = false;
	startsPaused = false;
	isFinished = false;
	
	snd = 0;
	
	position.X = 0.0f;
	position.Y = 0.0f;
	position.Z = 0.0f;

	sound3D = false;


}

std::string Component::Sound::getFile()
{
	return file;
}

vec3df Component::Sound::getPos()
{
	return position;
}

bool Component::Sound::getInitialized()
{
	return isInitialized;
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

bool Component::Sound::getFinished()
{
	isFinished = snd->isFinished();
	return isFinished;
}

irrklang::ISound * Component::Sound::getSound()
{
	return snd;
}

void Component::Sound::setFile(std::string f)
{
	file = f;
}

void Component::Sound::setInitialized(bool state)
{
	isInitialized = state;
}

void Component::Sound::setPlaying(bool state)
{
	isPlaying = state;
}

void Component::Sound::startPlaying2D(ISoundEngine* engine)
{
	isPlaying = true;
	snd = engine->play2D(this->getFile().c_str(), this->getLooping(),startsPaused, true);
}

void Component::Sound::startPlaying3D(ISoundEngine* engine)
{
	isPlaying = true;
	snd = engine->play3D(this->getFile().c_str(), position, this->getLooping(), startsPaused, true);
}

void Component::Sound::stopPlaying(ISoundEngine* engine)
{
	isPlaying = false;
	snd->stop();
}

void Component::Sound::setPause()
{
	isPlaying = false;
	snd->setIsPaused(true);
}

void Component::Sound::setSoundEmitterPosition(vec3df pos)
{
	snd->setPosition(pos);
	position = pos;
}

void Component::Sound::setSoundListenerPosition(ISoundEngine* engine, vec3df pos, vec3df lookDirection, vec3df velPerSecond, vec3df upVector)
{
	engine->setListenerPosition(pos, lookDirection, velPerSecond, upVector);
}

void Component::Sound::setPos(vec3df pos)
{
	position = pos;
}

void Component::Sound::setLooping(bool state)
{
	isLooping = state;
}

void Component::Sound::setPaused(bool state)
{
	startsPaused = state;
}

bool Component::Sound::getsound3D()
{
	return sound3D;
}

void Component::Sound::setSound3D(bool state)
{
	sound3D = state;
}
;
