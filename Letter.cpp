#include "Letter.h"

Letter::Letter() :
    character(' '),
    backgroundColor(sf::Color(180, 180, 180, 100)),
    textColor(sf::Color::Black),
    isRevealed(false) {
}

// Setters
void Letter::setCharacter(char c) {
    character = c;
}

void Letter::setBackgroundColor(sf::Color color) {
    backgroundColor = color;
}

void Letter::setTextColor(sf::Color color) {
    textColor = color;
}

void Letter::reveal() {
    isRevealed = true;
}

void Letter::reset() {
    character = ' ';
    backgroundColor = sf::Color(180, 180, 180, 100);
    textColor = sf::Color::Black;
    isRevealed = false;
}

// Getters
char Letter::getCharacter() const {
    return character;
}

sf::Color Letter::getBackgroundColor() const {
    return backgroundColor;
}

sf::Color Letter::getTextColor() const {
    return textColor;
}

bool Letter::isLetterRevealed() const {
    return isRevealed;
}
