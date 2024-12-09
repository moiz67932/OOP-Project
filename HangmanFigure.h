#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class HangmanFigure {
private:
    static const int maxIncorrectAttempts = 6; // Maximum attempts allowed
    sf::Texture textures[maxIncorrectAttempts]; // Array to store textures
    sf::Sprite sprites[maxIncorrectAttempts];  // Array to store sprites
    float opacity[maxIncorrectAttempts]; // Array to store opacity for each sprite
    float fadeSpeed; // Speed at which each sprite fades in
    sf::Clock fadeClock; // Clock to manage timing for fades

public:
    HangmanFigure();
    ~HangmanFigure();

    void loadTextures(const std::string& basePath); // Load textures from file paths
    void draw(sf::RenderWindow& window, int incorrectAttempts); // Draw the figure based on attempts

    void setFadeSpeed(float speed) { fadeSpeed = speed; } // Setter for fade speed
};
