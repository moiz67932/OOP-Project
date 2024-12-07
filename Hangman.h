//#pragma once
//#include "Game.h"
//class Hangman :
//    public Game
//{
//private:
//    void loadFont() override;
//    void loadBackground() override;
//public:
//    Hangman();  // Constructor
//    ~Hangman(); // Destructor
//
//    void startGame() override;
//    void endGame() override;
//    void render(sf::RenderWindow& window) override;
//
//};


#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameKeyboard.h"
#include "WordDictionary.h"
#include "Letter.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Hangman : public Game {
private:
    Letter letterGrid[6][5];
    GameKeyboard keyboard;
    WordDictionary dictionary;

    sf::Text messageText;
    sf::RectangleShape playAgainButton;
    sf::Text playAgainText;
    sf::RenderWindow* windowPtr;

    int incorrectAttempts;
    int maxAttempts;
    std::string targetWord;
    std::vector<char> guessedLetters;
    bool gameWon;
    bool gameOver;

    void loadFont();
    void loadBackground();
    void selectRandomWord();
    void checkLetter(char letter);
    void drawHangman();
    void renderGrid(sf::RenderWindow& window);
    void resetGame();

public:
    Hangman();
    ~Hangman();

    void initializeGame();
    void handleInput(sf::Event event);

    void startGame() override;
    void endGame() override;
    void render(sf::RenderWindow& window) override;

    bool shouldReturnToMenu;
};
