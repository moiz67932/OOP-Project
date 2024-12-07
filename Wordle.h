#pragma once
#include<SFML/Graphics.hpp>
#include "Game.h"
#include"GameKeyboard.h"
#include"WordDictionary.h"
#include "Letter.h"
#include <string>
#include <iostream> 

class Wordle : public Game
{
private:
    Letter letterGrid[6][5];
    GameKeyboard keyboard;
    WordDictionary dictionary;

    sf::Text messageText;
    sf::RectangleShape playAgainButton;
    sf::Text playAgainText;
    sf::RenderWindow* windowPtr;
    sf::RectangleShape backButton;
    sf::Text backButtonText;

    int currentRow;
    int currentColumn;
    std::string targetWord;
    bool showMessage;
    bool gameWon;

    void loadFont() override;
    void loadBackground() override;
    void selectRandomWord();
    void PlayAgainButton();
    void checkWord();
    void resetGame();

public:
    Wordle();
    ~Wordle();
    void initializeGrid();
    void renderGrid(sf::RenderWindow& window);
    void handleInput(sf::Event event);

    void startGame() override;
    void endGame() override;
    void render(sf::RenderWindow& window) override;

    bool shouldReturnToMenu;
};