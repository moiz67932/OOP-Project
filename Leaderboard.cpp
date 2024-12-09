#include "Leaderboard.h"

Leaderboard::Leaderboard() : leaderboardDataCount(0) {
    // Initialize leaderboardData to zero
    memset(leaderboardData, 0, sizeof(leaderboardData));
}

void Leaderboard::readPlayerData(const string& gameType) {
    leaderboardDataCount = 0;

    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(playersDirectory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename.length() > 5 && filename.substr(filename.length() - 5) == ".json") {
                string filepath = playersDirectory + filename;

                ifstream fileIn(filepath);
                if (fileIn.is_open()) {
                    json playerData;
                    fileIn >> playerData;
                    fileIn.close();

                    if (leaderboardDataCount < MAX_LEADERBOARD_ENTRIES) {
                        LeaderboardEntry& playerStats = leaderboardData[leaderboardDataCount];

                        strncpy_s(playerStats.name, playerData["name"].get<string>().c_str(),
                            sizeof(playerStats.name) - 1);
                        playerStats.name[sizeof(playerStats.name) - 1] = '\0';

                        if (gameType == "snake") {
                            playerStats.highestScore = playerData["snake"]["highestScore"].get<int>();
                            playerStats.gamesPlayed = 0;
                            playerStats.gamesWon = 0;
                            playerStats.totalTime = 0;
                        }
                        else if (gameType == "hangman") {
                            playerStats.gamesPlayed = playerData["hangman"]["gamesPlayed"].get<int>();
                            playerStats.gamesWon = playerData["hangman"]["gamesWon"].get<int>();
                            playerStats.totalTime = playerData["hangman"]["totalTime"].get<int>();
                            playerStats.highestScore = 0;
                        }
                        else {
                            playerStats.gamesPlayed = playerData[gameType]["gamesPlayed"].get<int>();
                            playerStats.gamesWon = playerData[gameType]["gamesWon"].get<int>();
                            playerStats.totalTime = playerData[gameType]["totalTime"].get<int>();
                            playerStats.highestScore = 0;
                        }

                        leaderboardDataCount++;
                    }
                }
            }
        }
        closedir(dir);
    }
}

void Leaderboard::customSort(const string& gameType) {
    // Custom bubble sort with game-specific sorting logic
    for (int i = 0; i < leaderboardDataCount - 1; i++) {
        for (int j = 0; j < leaderboardDataCount - i - 1; j++) {
            bool shouldSwap = false;

            if (gameType == "snake") {
                // Sort by highest score in descending order
                if (leaderboardData[j].highestScore < leaderboardData[j + 1].highestScore) {
                    shouldSwap = true;
                }
            }
            else {
                // For Wordle and Hangman: prioritize games won, then total time
                if (leaderboardData[j].gamesWon < leaderboardData[j + 1].gamesWon) {
                    shouldSwap = true;
                }
                else if (leaderboardData[j].gamesWon == leaderboardData[j + 1].gamesWon) {
                    // If games won are equal, compare total time
                    if (leaderboardData[j].totalTime > leaderboardData[j + 1].totalTime) {
                        shouldSwap = true;
                    }
                }
            }

            if (shouldSwap) {
                // Swap the stats
                LeaderboardEntry temp = leaderboardData[j];
                leaderboardData[j] = leaderboardData[j + 1];
                leaderboardData[j + 1] = temp;
            }
        }
    }

    // Assign ranks
    for (int i = 0; i < leaderboardDataCount; i++) {
        leaderboardData[i].rank = i + 1;
    }
}

LeaderboardEntry* Leaderboard::loadLeaderboard(const string& gameType) {
    // Read player data for the specific game type
    readPlayerData(gameType);

    // Sort the leaderboard based on game type
    customSort(gameType);

    return leaderboardData;
}

int Leaderboard::getLeaderboardCount() const {
    return leaderboardDataCount;
}

void Leaderboard::updatePlayerStats(const string& playerName, const string& gameType,bool gameWon,int gameTime,int score) {
    // Construct file path
    string fileName = playersDirectory + playerName + ".json";

    // Open and read the existing JSON file
    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        cerr << "Error: Could not open player file for updating stats." << endl;
        return;
    }

    json playerData;
    fileIn >> playerData;
    fileIn.close();

    // Initialize game-specific data if missing
    if (gameType == "hangman") {
        if (!playerData.contains("hangman")) {
            playerData["hangman"] = { {"gamesPlayed", 0}, {"gamesWon", 0}, {"totalTime", 0} };
        }
    }

    // Update statistics based on game type
    if (gameType == "snake") {
        // Update highest score
        int currentHighScore = playerData["snake"]["highestScore"].get<int>();
        if (score > currentHighScore) {
            playerData["snake"]["highestScore"] = score;
        }
    }
    else {
        // Wordle and Hangman statistics
        playerData[gameType]["gamesPlayed"] = playerData[gameType]["gamesPlayed"].get<int>() + 1;

        if (gameWon) {
            playerData[gameType]["gamesWon"] = playerData[gameType]["gamesWon"].get<int>() + 1;
        }

        playerData[gameType]["totalTime"] = playerData[gameType]["totalTime"].get<int>() + gameTime;
    }

    // Write updated data back to file
    ofstream fileOut(fileName);
    if (!fileOut.is_open()) {
        cerr << "Error: Could not open player file for writing." << endl;
        return;
    }

    fileOut << playerData.dump(4);
    fileOut.close();
}

void Leaderboard::display(sf::RenderWindow& window, const string& gameType, sf::Font& font) {
    // Display the leaderboard popup
    sf::RectangleShape leaderboardBackground(sf::Vector2f(600, 400));
    leaderboardBackground.setPosition(100, 100);
    leaderboardBackground.setFillColor(sf::Color(255, 255, 255, 200));
    window.draw(leaderboardBackground);

    // Display the leaderboard title
    sf::Text leaderboardTitle;
    leaderboardTitle.setFont(font);
    leaderboardTitle.setString(gameType.substr(0, 1) == "w" ? "Wordle Leaderboard" :
        gameType.substr(0, 1) == "s" ? "Snake Leaderboard" :
        "Game Leaderboard");
    leaderboardTitle.setCharacterSize(28);
    leaderboardTitle.setFillColor(sf::Color::Black);
    leaderboardTitle.setPosition(270, 120);
    window.draw(leaderboardTitle);

    // Get leaderboard data
    LeaderboardEntry* leaderboardEntries = loadLeaderboard(gameType);
    int count = getLeaderboardCount();

    // Define column positions and widths
    float colRank = 165;           
    float colName = 245;           
    float colGamesPlayed = 400;    
    float colGamesWon = 500;      
    float colTotalTime = 600;     
    float colHighestScore = 400;  

    // Display table headings
    sf::Text heading;
    heading.setFont(font);
    heading.setCharacterSize(20);
    heading.setFillColor(sf::Color::Black);
    heading.setPosition(colRank-15, 160);

    if (gameType == "snake") {
        heading.setString("Rank        Name                   Highest Score");
    }
    else {
        heading.setString("Rank        Name                   Played        Won          Time (s)");
    }
    window.draw(heading);

    // Display leaderboard data
    float yPos = 190;
    for (int i = 0; i < count && i < 10; ++i) {
        // Rank
        sf::Text rankText;
        rankText.setFont(font);
        rankText.setString(to_string(leaderboardEntries[i].rank));
        rankText.setCharacterSize(18);
        rankText.setFillColor(sf::Color::Black);
        rankText.setPosition(colRank, yPos);
        window.draw(rankText);

        // Name
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(leaderboardEntries[i].name);
        nameText.setCharacterSize(18);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(colName, yPos);
        window.draw(nameText);

        if (gameType == "snake") {
            // Snake: Highest Score
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setString(to_string(leaderboardEntries[i].highestScore));
            scoreText.setCharacterSize(18);
            scoreText.setFillColor(sf::Color::Black);
            scoreText.setPosition(colHighestScore, yPos);
            window.draw(scoreText);
        }
        else {
            // Wordle/Hangman: Games Played
            sf::Text gamesPlayedText;
            gamesPlayedText.setFont(font);
            gamesPlayedText.setString(to_string(leaderboardEntries[i].gamesPlayed));
            gamesPlayedText.setCharacterSize(18);
            gamesPlayedText.setFillColor(sf::Color::Black);
            gamesPlayedText.setPosition(colGamesPlayed, yPos);
            window.draw(gamesPlayedText);

            // Games Won
            sf::Text gamesWonText;
            gamesWonText.setFont(font);
            gamesWonText.setString(to_string(leaderboardEntries[i].gamesWon));
            gamesWonText.setCharacterSize(18);
            gamesWonText.setFillColor(sf::Color::Black);
            gamesWonText.setPosition(colGamesWon, yPos);
            window.draw(gamesWonText);

            // Total Time
            sf::Text totalTimeText;
            totalTimeText.setFont(font);
            totalTimeText.setString(to_string(leaderboardEntries[i].totalTime));
            totalTimeText.setCharacterSize(18);
            totalTimeText.setFillColor(sf::Color::Black);
            totalTimeText.setPosition(colTotalTime, yPos);
            window.draw(totalTimeText);
        }

        yPos += 25; // Move to the next row
    }

    // Close button
    sf::RectangleShape closeButton(sf::Vector2f(100, 40));
    closeButton.setPosition(350, 460);
    closeButton.setFillColor(sf::Color::Red);
    window.draw(closeButton);

    sf::Text closeText;
    closeText.setFont(font);
    closeText.setString("Close");
    closeText.setCharacterSize(20);
    closeText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = closeText.getLocalBounds();
    closeText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    closeText.setPosition(
        closeButton.getPosition().x + closeButton.getSize().x / 2.f,
        closeButton.getPosition().y + closeButton.getSize().y / 2.f
    );
    window.draw(closeText);
}

bool Leaderboard::isCloseButtonClicked(const sf::Vector2f& mousePos) const {
    sf::RectangleShape closeButton(sf::Vector2f(100, 40));
    closeButton.setPosition(350, 460);
    return closeButton.getGlobalBounds().contains(mousePos);
}
