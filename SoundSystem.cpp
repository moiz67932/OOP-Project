#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
}

SoundSystem::~SoundSystem()
{
}

void SoundSystem::initMusic(string& audioPath)
{
	if (!this->music.openFromFile(audioPath))
		cout << "Music Not Loaded!" << endl;
}

void SoundSystem::playMusic()
{
	this->music.play();
}

void SoundSystem::pauseMusic()
{
	this->music.pause();
}

void SoundSystem::setVolume(int volume)
{
	this->music.setVolume(volume);
}
