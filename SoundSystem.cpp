//#include "SoundSystem.h"
//
//SoundSystem::SoundSystem() : isMuted(false), volume(50) // Default volume at 50
//{
//    screen = nullptr;
//}
//
//SoundSystem::~SoundSystem()
//{
//}
//
//void SoundSystem::setScreen(Screen* screen)
//{
//    this->screen = screen;
//}
//
//void SoundSystem::initMusic(const string& audioPath)
//{
//    if (!this->music.openFromFile(audioPath))
//        std::cout << "Music Not Loaded!" << std::endl;
//}
//
//void SoundSystem::playMusic()
//{
//    currentState = screen->getCurrentState();
//    if (currentState == "menu") {
//        this->music.setVolume(this->volume);
//        this->music.play();
//    }
//}
//
//void SoundSystem::pauseMusic()
//{
//    this->music.pause();
//}
//
//void SoundSystem::toggleMute()
//{
//    this->isMuted = !this->isMuted;
//    this->music.setVolume(this->isMuted ? 0 : this->volume);
//}
//
//void SoundSystem::setVolume(int volume)
//{
//    this->volume = std::max(0, std::min(volume, 100)); // Clamp volume between 0 and 100
//    if (!this->isMuted)
//        this->music.setVolume(this->volume);
//}
//
//void SoundSystem::increaseVolume()
//{
//    setVolume(this->volume + 10);
//}
//
//void SoundSystem::decreaseVolume()
//{
//    setVolume(this->volume - 10);
//}
//
//bool SoundSystem::getIsMuted() const
//{
//    return this->isMuted;
//}






#include "SoundSystem.h"
#include "Screen.h"
#include "MainMenu.h"


SoundSystem::SoundSystem() : isMuted(false), volume(50), screen(nullptr) {
    loadTextures();
}

SoundSystem::~SoundSystem() {}

void SoundSystem::loadTextures() {
    if (!volumeOnTexture.loadFromFile("./assets/images/volume.png") ||
        !volumeOffTexture.loadFromFile("./assets/images/mute.png") ||
        !triangleTexture.loadFromFile("./assets/images/arrow.png") ||
        !plusTexture.loadFromFile("./assets/images/plus.png") ||
        !minusTexture.loadFromFile("./assets/images/minus.png")) {
        std::cout << "Error loading textures!" << std::endl;
    }

    volumeIcon.setTexture(volumeOnTexture);
    triangleIcon.setTexture(triangleTexture);
    plusIcon.setTexture(plusTexture);
    minusIcon.setTexture(minusTexture);

    volumeIcon.setPosition(700, 550);  // Bottom-right corner
    triangleIcon.setPosition(740, 550);
    plusIcon.setPosition(740, 520);
    minusIcon.setPosition(740, 580);
}

void SoundSystem::setScreen(Screen* screen) {
    if (!screen) {
            this->screen = screen;
    }
}

void SoundSystem::initMusic(const std::string& menuMusic, const std::string& gameMusic) {
        if (!music.openFromFile(menuMusic))
            std::cout << "Failed to load menu music!" << std::endl;
}

    void SoundSystem::updateMusicState() {
    //std::string state = screen->getCurrentState();
    std::string state = "menu";
    if (state != "menu" && music.getStatus() == sf::Music::Stopped) {
        initMusic("./assets/music/music.mp3", "./assets/music/music.mp3");  // Replace with actual file
        playMusic();
    }
    else if (state == "menu" && music.getStatus() == sf::Music::Stopped) {
        initMusic("./assets/music/music.mp3", "./assets/music/music.mp3");  // Replace with actual file
        playMusic();
    }
}

void SoundSystem::playMusic() {
    music.setVolume(isMuted ? 0 : volume);
    music.play();
}

void SoundSystem::pauseMusic() {
    music.pause();
}

void SoundSystem::toggleMute() {
    isMuted = !isMuted;
    music.setVolume(isMuted ? 0 : volume);
    volumeIcon.setTexture(isMuted ? volumeOffTexture : volumeOnTexture);
}

void SoundSystem::setVolume(int volume) {
    this->volume = (volume < 0) ? 0 : (volume > 100) ? 100 : volume;

    if (!isMuted) {
        music.setVolume(this->volume);
    }
}

void SoundSystem::increaseVolume() {
    setVolume(volume + 10);
}

void SoundSystem::decreaseVolume() {
    setVolume(volume - 10);
}

void SoundSystem::render(sf::RenderWindow& window) {
    window.draw(volumeIcon);
    window.draw(triangleIcon);
    window.draw(plusIcon);
    window.draw(minusIcon);
}

void SoundSystem::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (volumeIcon.getGlobalBounds().contains(mousePos)) {
            toggleMute();
        }
        else if (plusIcon.getGlobalBounds().contains(mousePos)) {
            increaseVolume();
        }
        else if (minusIcon.getGlobalBounds().contains(mousePos)) {
            decreaseVolume();
        }
    }
}
