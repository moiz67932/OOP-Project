#pragma once
#include <SFML/Graphics.hpp>
#include <cctype>
#include <string>
#include <iostream>

class GameKeyboard {
private:
    // Constants for keyboard layout
    static const int ROWS = 3;
    static const int MAX_KEYS_PER_ROW = 10;

    // Keyboard layout (QWERTY)
    char keyboardLayout[ROWS][MAX_KEYS_PER_ROW] = {
        {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
        {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\0'},
        {'Z', 'X', 'C', 'V', 'B', 'N', 'M', '\0', '\0', '\0'}
    };

    // Colors for each key
    sf::Color keyColors[26];

    // SFML text and shapes for rendering
    sf::Font font;
    sf::Text keyboardTexts[26];
    sf::RectangleShape keyboardBoxes[26];

    // Position and sizing constants
    const float KEY_WIDTH = 40.f;
    const float KEY_HEIGHT = 50.f;
    const float KEY_SPACING = 5.f;
    const sf::Vector2f START_POSITION = sf::Vector2f(175.f, 420.f);

    // Helper function to initialize keyboard visuals
    void initializeKeyboardDisplay();

public:
    // Constructor
    GameKeyboard();

    // Change color of a specific key
    void changeLetterColor(char letter, sf::Color color);

    // Render the keyboard
    void render(sf::RenderWindow& window);

    // Reset keyboard colors
    void resetKeyboard();
};