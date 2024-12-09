#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Snake.h"

void Snake::loadFont()
{
    if (!font.loadFromFile("./assets/fonts/font1.ttf"))
    {
        cout << "Font not loaded in Snake Game" << endl;
    }
    messageText.setFont(font);
    scoreText.setFont(font);
}

void Snake::loadBackground()
{
    // Load the background texture
    if (!backgroundTexture.loadFromFile("./assets/images/background.jpg"))
    {
        cout << "Background Loading Error :: Game.cpp" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Load the wall texture
   
}

Snake::Snake()
    : level(1), score(0), speed(5), gameOver(false), snakeSize(1), direction(0, 0)
{
    // Initialize snake at starting position
    snakeBody[0] = sf::Vector2i(400, 300); // Start in the middle of the window
}

void Snake::startGame()
{
    // Initialize game variables
    loadFont();
    loadBackground();
    score = 0;
    snakeSize = 1;
    direction = sf::Vector2i(0, -10); // Start by moving up
    spawnFood();
    gameOver = false;
    // lastMoveTime = sf::Time::Zero; // Reset last move time
}

void Snake::endGame()
{
    gameOver = true;
}

void Snake::handleInput(const sf::Event &event)
{
    // Change direction based on user input (arrow keys)
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up && direction != sf::Vector2i(0, 10))
        {
            direction = sf::Vector2i(0, -10); // Move up
        }
        else if (event.key.code == sf::Keyboard::Down && direction != sf::Vector2i(0, -10))
        {
            direction = sf::Vector2i(0, 10); // Move down
        }
        else if (event.key.code == sf::Keyboard::Left && direction != sf::Vector2i(10, 0))
        {
            direction = sf::Vector2i(-10, 0); // Move left
        }
        else if (event.key.code == sf::Keyboard::Right && direction != sf::Vector2i(-10, 0))
        {
            direction = sf::Vector2i(10, 0); // Move right
        }
    }
}

void Snake::updateGame()
{
    if (gameOver)
        return;

    // Move the snake body
    for (int i = snakeSize - 1; i > 0; --i)
    {
        snakeBody[i] = snakeBody[i - 1]; // Shift segments forward
    }

    // Update the head of the snake
    snakeBody[0] += direction;

    // Check for collisions with food
    if (snakeBody[0] == foodPosition)
    {
        score += 10;
        growSnake();
        spawnFood();
    }

    // Check if the snake intersects with itself or hits the wall
    if (IsSelfIntersecting() || snakeBody[0].x < 0 || snakeBody[0].x >= windowWidth || snakeBody[0].y < 0 || snakeBody[0].y >= windowHeight)
    {
        endGame();
    }
}

void Snake::render(sf::RenderWindow &window)
{
    if (gameOver)
    {
        // Display game over message
        messageText.setString("Game Over! Press R to restart.");
        window.draw(messageText);
    }
    else
    {
        // Draw the walls (boundary)
        window.draw(backgroundSprite);
        //window.draw(wallSprite);

        // Draw the snake
        for (int i = 0; i < snakeSize; ++i)
        {
            sf::RectangleShape segment(sf::Vector2f(10, 10)); // Each segment is a 10x10 rectangle
            segment.setPosition(snakeBody[i].x, snakeBody[i].y);
            segment.setFillColor(sf::Color::Green);
            window.draw(segment);
        }

        // Draw food
        sf::RectangleShape food(sf::Vector2f(10, 10));
        food.setPosition(foodPosition.x, foodPosition.y);
        food.setFillColor(sf::Color::Red);
        window.draw(food);
    }
}

void Snake::spawnFood()
{
    // Spawn food at a random position within the window
    foodPosition = sf::Vector2i(rand() % windowWidth, rand() % windowHeight);
}

void Snake::growSnake()
{
    if (snakeSize < maxSnakeLength)
    {
        ++snakeSize; // Increase snake size
    }
}

bool Snake::isGameOver() const
{
    return gameOver;
}

bool Snake::IsSelfIntersecting() const
{
    // Check if the snake's head intersects with its body
    for (int i = 1; i < snakeSize; ++i)
    {
        if (snakeBody[0] == snakeBody[i])
        {
            return true;
        }
    }
    return false;
}






















//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <iostream>
//#include "Snake.h"
//#include <sstream>
//#include <time.h>
//
//std::string to_string(int num) {
//    std::stringstream ss;
//    ss << num;
//    return ss.str();
//}
//
//void Snake::loadFont()
//{
//    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
//        cout << "Font Loading Error :: MainMenu.cpp" << endl;
//    }
//}
//
//void Snake::loadBackground()
//{
//    // Load the background texture
//    if (!backgroundTexture.loadFromFile("./assets/images/backgroundWordle.jpg")) {
//        cout << "Background Loading Error :: Game.cpp" << endl;
//    }
//    backgroundSprite.setTexture(backgroundTexture);
//}
//
//SnakeSegment::SnakeSegment(int x, int y) {
//    position.x = x;
//    position.y = y;
//}
//
//SnakeSegment::SnakeSegment() {
//    position.x = -1;
//    position.y = -1;
//}
//
//Grid::Grid(int rows, int cols, int cellSize)
//    : rows(rows), cols(cols), cellSize(cellSize) {
//    gridTexture.loadFromFile("back1.png");
//    snakeTexture.loadFromFile("Snake.png");
//    fruitTexture.loadFromFile("food.png");
//
//    gridSprite.setTexture(gridTexture);
//    snakeSprite.setTexture(snakeTexture);
//    fruitSprite.setTexture(fruitTexture);
//}
//
//void Grid::drawGrid(sf::RenderWindow& window) {
//    for (int i = 0; i < cols; i++) {
//        for (int j = 0; j < rows; j++) {
//            gridSprite.setPosition(i * cellSize, j * cellSize);
//            window.draw(gridSprite);
//        }
//    }
//}
//
//Snake::Snake()
//    : grid(800, 600, 10), direction(0), score(0), highestScore(0),
//    snakeSize(2), timer(0), delay(0.1), isGameOver(false) {
//    srand(time(0));
//    spawnFruit();
//
//    snake[0] = SnakeSegment(10, 10);
//    snake[1] = SnakeSegment(10, 11);
//
//    font.loadFromFile("font1.ttf");
//    scoreText.setFont(font);
//    scoreText.setFillColor(sf::Color::White);
//    scoreText.setPosition(10, 10);
//    scoreText.setCharacterSize(18);
//
//    highestScoreText.setFont(font);
//    highestScoreText.setFillColor(sf::Color::White);
//    highestScoreText.setPosition(400, 10);
//    highestScoreText.setCharacterSize(18);
//
//    gameOverText.setFont(font);
//    gameOverText.setFillColor(sf::Color::White);
//    gameOverText.setCharacterSize(30);
//    gameOverText.setString("");
//}
//
//
//void Snake::spawnFruit() {
//    do {
//        fruit.x = rand() % grid.cols;
//        fruit.y = rand() % grid.rows;
//    } while (isFruitOnSnake());
//}
//
//bool Snake::isFruitOnSnake() {
//    for (int i = 0; i < snakeSize; i++) {
//        if (snake[i].position.x == fruit.x && snake[i].position.y == fruit.y) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void Snake::updateSnake() {
//    if (snakeSize > 0) {
//        for (int i = snakeSize; i > 0; --i) {
//            snake[i].position = snake[i - 1].position;
//        }
//
//        if (direction == 0) snake[0].position.y += 1;
//        if (direction == 1) snake[0].position.x -= 1;
//        if (direction == 2) snake[0].position.x += 1;
//        if (direction == 3) snake[0].position.y -= 1;
//
//        if (snake[0].position.x == fruit.x && snake[0].position.y == fruit.y) {
//            snakeSize++;
//            score++;
//            if (score > highestScore) highestScore = score;
//            spawnFruit();
//        }
//
//        static int previousScore = -1;
//        if (score % 5 == 0 && score != 0 && score != previousScore) {
//            delay -= 0.01;
//            previousScore = score;
//        }
//
//        if (snake[0].position.x >= grid.cols) snake[0].position.x = 0;
//        if (snake[0].position.x < 0) snake[0].position.x = grid.cols - 1;
//        if (snake[0].position.y >= grid.rows) snake[0].position.y = 0;
//        if (snake[0].position.y < 0) snake[0].position.y = grid.rows - 1;
//
//        for (int i = 1; i < snakeSize; i++) {
//            if (snake[0].position.x == snake[i].position.x &&
//                snake[0].position.y == snake[i].position.y) {
//                gameOver();
//                break;
//            }
//        }
//    }
//}
//
//void Snake::resetGame() {
//    snakeSize = 2;
//    snake[0] = SnakeSegment(10, 10);
//    snake[1] = SnakeSegment(10, 11);
//    score = 0;
//    delay = 0.1;
//    spawnFruit();
//    isGameOver = false;
//}
//
//void Snake::gameOver() {
//    isGameOver = true;
//    gameOverText.setString("Game Over! Press R to Restart");
//    gameOverText.setPosition(grid.cols * grid.cellSize / 4, grid.rows * grid.cellSize / 2);
//    gameOverText.setCharacterSize(30);
//    gameOverText.setFillColor(sf::Color::Red);
//}
//
//void Snake::updateScoreText() {
//    scoreText.setString("Current Score: " + (score));
//    highestScoreText.setString("Highest Score: " + (highestScore));
//}
//
//void Snake::handleInput() {
//    if (isGameOver) {
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
//            resetGame();
//            gameOverText.setString("");
//        }
//        return;
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != 2) direction = 1;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != 1) direction = 2;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != 0) direction = 3;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != 3) direction = 0;
//}
//
//void Snake::update(float timeElapsed) {
//    if (!isGameOver) {
//        timer += timeElapsed;
//        if (timer > delay) {
//            timer = 0;
//            updateSnake();
//        }
//    }
//    updateScoreText();
//}
//
//void Snake::startGame()
//{
//}
//
//void Snake::endGame()
//{
//}
//
//void Snake::render(sf::RenderWindow& window) {
//    grid.drawGrid(window);
//
//    for (int i = 0; i < snakeSize; i++) {
//        snakeSprite.setPosition(snake[i].position.x * grid.cellSize, snake[i].position.y * grid.cellSize);
//        window.draw(snakeSprite);
//    }
//
//    fruitSprite.setPosition(fruit.x * grid.cellSize, fruit.y * grid.cellSize);
//    window.draw(fruitSprite);
//
//    window.draw(scoreText);
//    window.draw(highestScoreText);
//
//    if (isGameOver) {
//        window.draw(gameOverText);
//    }
//}
