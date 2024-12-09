#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameKeyboard.h"
#include "WordDictionary.h"
#include "HangmanFigure.h"
#include "Letter.h"
#include "SoundSystem.h"
#include "Player.h"
#include "AchievementSystem.h"
#include "Leaderboard.h"
#include "PauseResumeHandler.h" 
#include "Category.h"
#include <fstream>
#include <cstdio>
#include "dirent.h"

#include <string>
#include <iostream>
#include <algorithm>

class Hangman : public Game {
private:
    sf::Texture wrongEntryTextures[6];
    sf::Sprite wrongEntrySprites[6];
    int maxIncorrectAttempts = 6;
    Letter letterGrid[6][5];
    GameKeyboard keyboard;
    WordDictionary dictionary;
    HangmanFigure hangmanFigure;
    //Player* currentPlayer;
    //AchievementSystem achievements; // Track achievements
    //Leaderboard leaderboard; // Manage leaderboard
    Category category;
    PauseResumeHandler pauseResumeHandler;



    // Category object
    int selectedCategoryIndex;    // The category chosen by the player
    std::string selectedCategory;
    sf::Text messageText;
    sf::RectangleShape playAgainButton;
    sf::Text playAgainText;
    sf::RenderWindow* windowPtr;
    sf::RectangleShape progressBarBackground; // Background for the progress bar
    sf::RectangleShape progressBar;
    sf::Text progressBarText;

    int incorrectAttempts;
    int maxAttempts;
    std::string targetWord;
    char guessedLetters[26];  // Fixed-size array for guessed letters
    int guessedLettersCount;  // Counter for the number of guessed letters
    bool gameWon;
    bool gameOver;
    bool gamePaused;
    int totalLives;

    void loadFont();
    void loadBackground();
    void loadWrongEntrySprites();
    void checkLetter(char letter);
    void drawHangman(sf::RenderWindow& window);
    void renderGrid(sf::RenderWindow& window);
    void resetGame();
    void updateLivesText();
    void updateProgressBar();

    // Player Settings
    sf::Text playerNameText;
    sf::RectangleShape playerNameBorder;
    Player* currentPlayer;
    sf::Clock gameTimer;

    // Leaderboard
    sf::Text leaderboardText;
    Leaderboard leaderboard;
    LeaderboardEntry leaderboardData[10];
    int leaderboardDataCount;
    bool showLeaderboard = false;



public:
    Hangman();
    ~Hangman();
    void checkWordCompletion();
    void initializeGame();
    void handleInput(sf::Event event, sf::RenderWindow& window);

    void startGame() override;
    void endGame() override;
    void render(sf::RenderWindow& window) override;
    void displayCategories(sf::RenderWindow& window); // Show category options
    void selectCategory(int categoryIndex);           // Set selected category
    std::string getRandomWordFromCategory(int categoryIndex);

    //Player
    void setPlayer(Player* player);
    void renderLeaderboard(sf::RenderWindow& window);

    void updateStats();

    bool shouldReturnToMenu;
};
