#pragma once
#include <SFML/Graphics.hpp>

class Letter {
private:
    char character;           
    sf::Color backgroundColor;
    sf::Color textColor;      
    bool isRevealed;          

public:
    Letter();

    // Setters
    void setCharacter(char c);
    void setBackgroundColor(sf::Color color);
    void setTextColor(sf::Color color);
    void reveal();
    void reset();

    // Getters
    char getCharacter() const;
    sf::Color getBackgroundColor() const;
    sf::Color getTextColor() const;
    bool isLetterRevealed() const;
};
