#pragma once
#include<SFML/Audio.hpp>
#include<string>
#include<iostream>
using namespace std;

class SoundSystem
{
private:
	sf::Music music;
public:
	SoundSystem();
	virtual ~SoundSystem();
	void initMusic(string& audioPath);
	void playMusic();
	void pauseMusic();
	void setVolume(int volume);
};

