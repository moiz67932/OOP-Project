#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include<iostream>

using namespace std;

class Snake : public Game {
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
    sf::Text messageText, scoreText;
    const int windowWidth = 800;
    const int windowHeight = 600;

    void spawnFood();
    //void chooseSpeed();
    void growSnake();
    bool isGameOver() const;
    bool IsSelfIntersecting() const;
};


// Represents a point in the grid
//struct Point {
//    int x, y;
//};
//
//// Represents a single segment of the snake
//class SnakeSegment {
//public:
//    Point position;
//
//    SnakeSegment(int x, int y);
//    SnakeSegment();
//};
//
//// Represents the grid and other game components
//class Grid {
//public:
//    int rows, cols, cellSize;
//    sf::Texture gridTexture, snakeTexture, fruitTexture;
//    sf::Sprite gridSprite, snakeSprite, fruitSprite;
//
//    Grid(int rows, int cols, int cellSize);
//    void drawGrid(sf::RenderWindow& window);
//};
//
//// Manages the game logic and rendering
//class Snake : public Game {
//private:
//    Grid grid;
//    SnakeSegment snake[100];
//    Point fruit;
//    int direction, score, highestScore, snakeSize;
//    float timer, delay;
//    sf::Font font;
//    sf::Text scoreText, highestScoreText;
//    sf::Text gameOverText;
//    bool isGameOver;
//    sf::Sprite snakeSprite;
//    sf::Sprite fruitSprite;
//
//    // Add to SnakeGame class
//    int level; // Track current level
//    float levelDisplayTimer; // Timer for level display
//    bool showLevelText;
//
//    void loadFont() override;
//    void loadBackground() override;
//    sf::Text levelText;
//
//    void spawnFruit();
//    bool isFruitOnSnake();
//    void updateSnake();
//    void resetGame();
//    void gameOver();
//    void updateScoreText();
//
//public:
//    Snake();
//
//    void handleInput();
//    void update(float timeElapsed);
//    void startGame() override;
//    void endGame() override;
//    void render(sf::RenderWindow& window);
//};
