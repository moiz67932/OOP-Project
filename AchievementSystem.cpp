#include "AchievementSystem.h"
#include <iostream>
#include <fstream>

void AchievementSystem::updateAchievement(const std::string& game, int score) {
    if (gameAchievements[game] < score) {
        gameAchievements[game] = score;
    }
}

void AchievementSystem::saveAchievements(std::ofstream& file) const {
    for (const auto& entry : gameAchievements) {
        file << entry.first << " " << entry.second << "\n";
    }
}

void AchievementSystem::loadAchievements(std::ifstream& file) {
    std::string game;
    int score;
    while (file >> game >> score) {
        gameAchievements[game] = score;
    }
}

void AchievementSystem::displayAchievements() const {
    for (const auto& entry : gameAchievements) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}
