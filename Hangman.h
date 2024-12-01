#pragma once
#include "Game.h"
class Hangman :
    public Game
{
private:
    void loadFont() override;
    void loadBackground() override;
public:
    Hangman();  // Constructor
    ~Hangman(); // Destructor

    void startGame() override;
    void endGame() override;
    void render(sf::RenderWindow& window) override;

};
