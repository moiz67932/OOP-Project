#include "Hangman.h"
#include <iostream>

void Hangman::loadFont()
{
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        cout << "Font Loading Error :: MainMenu.cpp" << endl;
    }
}

void Hangman::loadBackground()
{
    // Load the background texture
    if (!backgroundTexture.loadFromFile("./assets/images/Wordle.png")) {
        cout << "Background Loading Error :: Game.cpp" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

Hangman::Hangman() {
    std::cout << "Hangman Game Initialized!" << std::endl;
    loadFont();
    loadBackground();
    // Initialize resources for Hangman game (e.g., set up hangman figure, load word categories)
}

Hangman::~Hangman() {
    std::cout << "Hangman Game Destroyed!" << std::endl;
    // Clean up resources
}

void Hangman::startGame() {
    std::cout << "Starting Hangman Game!" << std::endl;
    // Set up the Hangman game (e.g., select a random word, reset lives)
}

void Hangman::endGame() {
    std::cout << "Ending Hangman Game!" << std::endl;
    // Cleanup or save progress
}

void Hangman::render(sf::RenderWindow& window) {
    // Display the hangman figure, current word progress, and remaining lives
    window.draw(backgroundSprite);
}
