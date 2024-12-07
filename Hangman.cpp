//#include "Hangman.h"
//#include <iostream>
//
//void Hangman::loadFont()
//{
//    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
//        cout << "Font Loading Error :: MainMenu.cpp" << endl;
//    }
//}
//
//void Hangman::loadBackground()
//{
//    // Load the background texture
//    if (!backgroundTexture.loadFromFile("./assets/images/Wordle.png")) {
//        cout << "Background Loading Error :: Game.cpp" << endl;
//    }
//    backgroundSprite.setTexture(backgroundTexture);
//}
//
//Hangman::Hangman() {
//    std::cout << "Hangman Game Initialized!" << std::endl;
//    loadFont();
//    loadBackground();
//    // Initialize resources for Hangman game (e.g., set up hangman figure, load word categories)
//}
//
//Hangman::~Hangman() {
//    std::cout << "Hangman Game Destroyed!" << std::endl;
//    // Clean up resources
//}
//
//void Hangman::startGame() {
//    std::cout << "Starting Hangman Game!" << std::endl;
//    // Set up the Hangman game (e.g., select a random word, reset lives)
//}
//
//void Hangman::endGame() {
//    std::cout << "Ending Hangman Game!" << std::endl;
//    // Cleanup or save progress
//}
//
//void Hangman::render(sf::RenderWindow& window) {
//    // Display the hangman figure, current word progress, and remaining lives
//    window.draw(backgroundSprite);
//}





#include "Hangman.h"

Hangman::Hangman() {
    std::cout << "Hangman Game Initialized!" << std::endl;
    loadFont();
    loadBackground();
    initializeGame();
    incorrectAttempts = 0;
    gameWon = false;
    gameOver = false;
    shouldReturnToMenu = false;
}

Hangman::~Hangman() {
    std::cout << "Hangman Game Destroyed!" << std::endl;
}

void Hangman::loadFont() {
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        std::cout << "Font Loading Error!" << std::endl;
    }
}

void Hangman::loadBackground() {
    if (!backgroundTexture.loadFromFile("./assets/images/background.jpg")) {
        std::cout << "Background Loading Error!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Hangman::selectRandomWord() {
    dictionary.getRandomWord(targetWord);
    std::transform(targetWord.begin(), targetWord.end(), targetWord.begin(), ::toupper);
}

void Hangman::initializeGame() {
    guessedLetters.clear();
    incorrectAttempts = 0;
    gameWon = false;
    gameOver = false;
    selectRandomWord();

    for (int i = 0; i < targetWord.size(); ++i) {
        letterGrid[0][i].setCharacter('_');
        letterGrid[0][i].setBackgroundColor(sf::Color::White);
        letterGrid[0][i].setTextColor(sf::Color::Black);
    }
}

void Hangman::checkLetter(char letter) {
    bool letterFound = false;
    for (int i = 0; i < targetWord.size(); ++i) {
        if (targetWord[i] == letter) {
            letterGrid[0][i].reveal();
            letterFound = true;
        }
    }

    if (!letterFound) {
        incorrectAttempts++;
    }

    if (incorrectAttempts >= 6) {
        gameOver = true;
    }

    gameWon = true;
    for (int i = 0; i < targetWord.size(); ++i) {
        if (!letterGrid[0][i].isLetterRevealed()) {
            gameWon = false;
            break;
        }
    }

    if (gameWon) {
        gameOver = true;
    }
}

void Hangman::drawHangman() {
    if (incorrectAttempts >= 1) {
        std::cout << "No Bro" << endl;
    }
    if (incorrectAttempts >= 2) {
        std::cout << "Please" << endl;
    }
    if (incorrectAttempts >= 3) {
        std::cout << "Why" << endl;
    }
    if (incorrectAttempts >= 4) {
        std::cout << "Careful" << endl;
    }
    if (incorrectAttempts >= 5) {
        std::cout << "Broooooooo" << endl;
    }
    if (incorrectAttempts >= 6) {
        std::cout << "Dead" << endl;
    }
}

void Hangman::renderGrid(sf::RenderWindow& window) {
    for (int i = 0; i < targetWord.size(); ++i) {
        sf::Text letterText;
        letterText.setFont(font);
        letterText.setString(std::string(1, letterGrid[0][i].getCharacter()));
        letterText.setCharacterSize(50);
        letterText.setFillColor(letterGrid[0][i].getTextColor());
        letterText.setPosition(200.f + i * 60.f, 150.f);
        window.draw(letterText);
    }
}

void Hangman::handleInput(sf::Event event) {
    if (gameOver) return;

    if (event.type == sf::Event::TextEntered) {
        if (std::isalpha(event.text.unicode)) {
            char guessedLetter = std::toupper(event.text.unicode);
            if (std::find(guessedLetters.begin(), guessedLetters.end(), guessedLetter) == guessedLetters.end()) {
                guessedLetters.push_back(guessedLetter);
                checkLetter(guessedLetter);
            }
        }
    }
}

void Hangman::startGame() {
    std::cout << "Starting Hangman Game!" << std::endl;
    initializeGame();
}

void Hangman::endGame() {
    if (gameWon) {
        std::cout << "You WON the game!" << std::endl;
    }
    else {
        std::cout << "You LOST the game! The word was: " << targetWord << std::endl;
    }
    resetGame();
}

void Hangman::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    renderGrid(window);
    drawHangman();

    if (gameOver) {
        messageText.setFont(font);
        messageText.setString(gameWon ? "You WON!" : "Game Over! The word was: " + targetWord);
        messageText.setCharacterSize(24);
        messageText.setFillColor(sf::Color::Red);
        messageText.setPosition(280.f, 300.f);
        window.draw(messageText);
    }

    keyboard.render(window);
    
}

void Hangman::resetGame() {
    gameWon = false;
    gameOver = false;
    incorrectAttempts = 0;
    guessedLetters.clear();
    initializeGame();
}
