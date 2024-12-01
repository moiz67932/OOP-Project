#include "Snake.h"
#include <iostream> // For debugging/logging (optional)

void Snake::loadFont()
{
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        cout << "Font Loading Error :: MainMenu.cpp" << endl;
    }
}

void Snake::loadBackground()
{
    // Load the background texture
    if (!backgroundTexture.loadFromFile("./assets/images/background.jpg")) {
        cout << "Background Loading Error :: Game.cpp" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

Snake::Snake() {
    std::cout << "Snake Game Initialized!" << std::endl;
    // Initialize snake game resources
    loadFont();
    loadBackground();
}

Snake::~Snake() {
    // Cleanup resources
    std::cout << "Snake Game Destroyed!" << std::endl;
}

void Snake::startGame() {
    std::cout << "Starting Snake Game!" << std::endl;
    // Initialize game logic
}

void Snake::endGame() {
    std::cout << "Ending Snake Game!" << std::endl;
    // Cleanup game logic
}

void Snake::render(sf::RenderWindow& window) {
    // Render game-specific elements
    window.draw(backgroundSprite);
}
