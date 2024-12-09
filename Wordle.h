#pragma once
#include<SFML/Graphics.hpp>
#include "Game.h"
#include "GameKeyboard.h"
#include "WordDictionary.h"
#include "Letter.h"
#include <string>
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include "dirent.h"
#include "PauseResumeHandler.h" 
#include"Leaderboard.h"


using namespace std;

// Struct to hold player stats
struct WordlePlayerStats {
    char name[50];
    int gamesPlayed;
    int gamesWon;
    int totalTime;
    int rank;
};

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
    PauseResumeHandler pauseResumeHandler;


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
    Wordle();
    ~Wordle();
    void initializeGrid();
    void renderGrid(sf::RenderWindow& window);
    void updateStats();
    void handleInput(sf::Event event, sf::RenderWindow* window);


    void startGame() override;
    void endGame() override;
    void render(sf::RenderWindow& window) override;

    //Player
    void setPlayer(Player* player);
    void renderLeaderboard(sf::RenderWindow& window);

    bool shouldReturnToMenu;
};