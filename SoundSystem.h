//#pragma once
//#include"Screen.h"
//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <string>
//#include <iostream>
//using namespace std;
//
//class SoundSystem
//{
//private:
//    sf::Music music;
//    bool isMuted;
//    int volume;
//    Screen* screen;
//    string currentState;
//
//public:
//    SoundSystem();
//    virtual ~SoundSystem();
//    void setScreen(Screen* screen);
//    void initMusic(const string& audioPath);
//    void playMusic();
//    void pauseMusic();
//    void toggleMute();
//    void setVolume(int volume);
//    void increaseVolume();
//    void decreaseVolume();
//    bool getIsMuted() const;
//};


#pragma once
class Screen; // Forward declaration
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class SoundSystem {
private:
    sf::Music music;
    bool isMuted;
    int volume;
    Screen* screen;
    sf::Texture volumeOnTexture, volumeOffTexture, triangleTexture, plusTexture, minusTexture;
    sf::Sprite volumeIcon, triangleIcon, plusIcon, minusIcon;

    void loadTextures();

public:
    SoundSystem();
    virtual ~SoundSystem();

    void setScreen(Screen* screen);
    void initMusic(const std::string& menuMusic, const std::string& gameMusic);
    void updateMusicState();
    void playMusic();
    void pauseMusic();
    void toggleMute();
    void setVolume(int volume);
    void increaseVolume();
    void decreaseVolume();
    void render(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);
};
