#pragma once

#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace std;

class Menu {
private:
    string menuOptions[3];
    sf::FloatRect gameOptionsBoundaries[3];
    sf::Font font;
    sf::Texture backgroundTexture;  
    sf::Sprite backgroundSprite;

    // Private Functions
    void loadFont();
    void loadBackground();
public:
    Menu();
    int checkClick(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
};