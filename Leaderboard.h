#pragma once
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "dirent.h"

using json = nlohmann::json;
using namespace std;

struct LeaderboardEntry {
    char name[50];
    int gamesPlayed;
    int gamesWon;
    int totalTime;
    int highestScore;
    int rank;
};

class Leaderboard {
private:
    static const int MAX_LEADERBOARD_ENTRIES = 10;
    LeaderboardEntry leaderboardData[MAX_LEADERBOARD_ENTRIES];
    int leaderboardDataCount;
    string playersDirectory = "./players/";

    void readPlayerData(const string& gameType);
    void customSort(const string& gameType);

public:
    Leaderboard();
    LeaderboardEntry* loadLeaderboard(const string& gameType);
    int getLeaderboardCount() const;
    void display(sf::RenderWindow& window, const string& gameType, sf::Font& font);

    bool isCloseButtonClicked(const sf::Vector2f& mousePos) const;

    void updatePlayerStats(const string& playerName,
        const string& gameType,
        bool gameWon = false,
        int gameTime = 0,
        int score = 0);
};