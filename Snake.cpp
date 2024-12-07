//#include "Snake.h"
//#include <iostream> // For debugging/logging (optional)
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
//    if (!backgroundTexture.loadFromFile("./assets/images/background.jpg")) {
//        cout << "Background Loading Error :: Game.cpp" << endl;
//    }
//    backgroundSprite.setTexture(backgroundTexture);
//}
//
//Snake::Snake() {
//    std::cout << "Snake Game Initialized!" << std::endl;
//    // Initialize snake game resources
//    loadFont();
//    loadBackground();
//}
//
//Snake::~Snake() {
//    // Cleanup resources
//    std::cout << "Snake Game Destroyed!" << std::endl;
//}
//
//void Snake::startGame() {
//    std::cout << "Starting Snake Game!" << std::endl;
//    // Initialize game logic
//}
//
//void Snake::endGame() {
//    std::cout << "Ending Snake Game!" << std::endl;
//    // Cleanup game logic
//}
//
//void Snake::render(sf::RenderWindow& window) {
//    // Render game-specific elements
//    window.draw(backgroundSprite);
//}




#include "Snake.h"


void Snake::loadFont()
{
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        cout << "Font Loading Error :: MainMenu.cpp" << endl;
    }
}

void Snake::loadBackground()
{
    // Load the background texture
    if (!backgroundTexture.loadFromFile("./assets/images/background.jpg")) {
        cout << "Background Loading Error :: Game.cpp" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

Snake::Snake() : level(1), score(0), speed(100), direction(1, 0), gameOver(false) {
    snakeBody[0] = sf::Vector2i(10, 10);
    snakeSize = 1;
}

void Snake::startGame() {
    level = 1;
    score = 0;
    direction = sf::Vector2i(1, 0);
    gameOver = false;
    snakeSize = 1;
    snakeBody[0] = sf::Vector2i(10, 10);
    chooseSpeed();
    spawnFood();
}

void Snake::endGame()
{
}

void Snake::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up && direction != sf::Vector2i(0, 1)) {
            direction = sf::Vector2i(0, -1);
        }
        else if (event.key.code == sf::Keyboard::Down && direction != sf::Vector2i(0, -1)) {
            direction = sf::Vector2i(0, 1);
        }
        else if (event.key.code == sf::Keyboard::Left && direction != sf::Vector2i(1, 0)) {
            direction = sf::Vector2i(-1, 0);
        }
        else if (event.key.code == sf::Keyboard::Right && direction != sf::Vector2i(-1, 0)) {
            direction = sf::Vector2i(1, 0);
        }
    }
}

void Snake::updateGame() {
    if (gameOver) return;

    sf::Vector2i newHead = snakeBody[0] + direction;
    for (int i = snakeSize - 1; i > 0; --i) {
        snakeBody[i] = snakeBody[i - 1];
    }
    snakeBody[0] = newHead;

    if (newHead == foodPosition) {
        score++;
        if (score % 5 == 0) {
            level++;
            speed -= 10;
            std::cout << "Level Up! Current Level: " << level << std::endl;
        }
        growSnake();
        spawnFood();
    }

    bool collisionWithSelf = false;
    for (int i = 1; i < snakeSize; ++i) {
        if (snakeBody[i] == newHead) {
            collisionWithSelf = true;
            break;
        }
    }

    if (newHead.x < 0 || newHead.y < 0 || newHead.x >= windowWidth / 20 || newHead.y >= windowHeight / 20 || collisionWithSelf) {
        gameOver = true;
        std::cout << "Game Over!" << std::endl;
    }
}

void Snake::render(sf::RenderWindow& window) {
    if (gameOver) return;

    sf::RectangleShape snakeSegment(sf::Vector2f(20.f, 20.f));
    for (int i = 0; i < snakeSize; i++) {
        snakeSegment.setPosition(snakeBody[i].x * 20.f, snakeBody[i].y * 20.f);
        snakeSegment.setFillColor(sf::Color::Green);
        window.draw(snakeSegment);
    }

    sf::RectangleShape food(sf::Vector2f(20.f, 20.f));
    food.setPosition(foodPosition.x * 20.f, foodPosition.y * 20.f);
    food.setFillColor(sf::Color::Red);
    window.draw(food);

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString("Level: " + std::to_string(level));
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(10.f, 10.f);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 40.f);

    window.draw(levelText);
    window.draw(scoreText);
}

void Snake::spawnFood() {
    foodPosition = sf::Vector2i(rand() % (windowWidth / 20), rand() % (windowHeight / 20));
}

void Snake::chooseSpeed() {
    std::cout << "Choose your game speed (slow, medium, fast): ";
    std::string speedChoice;
    std::cin >> speedChoice;

    if (speedChoice == "slow") {
        speed = 150;
    }
    else if (speedChoice == "medium") {
        speed = 100;
    }
    else if (speedChoice == "fast") {
        speed = 50;
    }
    else {
        std::cout << "Invalid choice. Defaulting to medium speed." << std::endl;
        speed = 100;
    }
}

void Snake::growSnake() {
    if (snakeSize < maxSnakeLength) {
        snakeSize++;
    }
}
