//#pragma once
//#include "Game.h"
//class Snake :
//    public Game
//{
//private:
//    void loadFont() override;
//    void loadBackground() override;
//public:
//    Snake();  // Constructor
//    ~Snake(); // Destructor
//
//    void startGame() override;
//    void endGame() override;
//    void render(sf::RenderWindow& window) override;
//
//private:
//};
//


#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class Snake : public Game{
public:
    Snake();
    void startGame();
    void endGame();
    void handleInput(const sf::Event& event);
    void updateGame();
    void render(sf::RenderWindow& window);
    void loadFont();
    void loadBackground();

private:
    int level;
    int score;
    int speed;
    sf::Vector2i direction;
    bool gameOver;
    static const int maxSnakeLength = 100;
    sf::Vector2i snakeBody[maxSnakeLength];
    int snakeSize;
    sf::Vector2i foodPosition;
    const int windowWidth = 800;
    const int windowHeight = 600;

    void spawnFood();
    void chooseSpeed();
    void growSnake();
};

#endif // SNAKE_H
