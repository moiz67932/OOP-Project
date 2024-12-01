#pragma once
#include "Game.h"
class Snake :
    public Game
{
private:
    void loadFont() override;
    void loadBackground() override;
public:
    Snake();  // Constructor
    ~Snake(); // Destructor

    void startGame() override;
    void endGame() override;
    void render(sf::RenderWindow& window) override;

private:
};

