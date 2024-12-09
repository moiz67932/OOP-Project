#pragma once
#include<string>
#include<SFML/Graphics.hpp>
using namespace std;

class Game {
protected:
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Protected Functions
    virtual void loadFont() = 0;
    virtual void loadBackground() = 0;

public:
    std::string name;

    virtual void startGame() = 0;
    virtual void endGame() = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~Game() {};
};
