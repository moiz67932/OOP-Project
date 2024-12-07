#pragma once
#include <string>
#include <unordered_map>

class AchievementSystem {
private:
    std::unordered_map<std::string, int> gameAchievements;

public:
    void updateAchievement(const std::string& game, int score);
    void saveAchievements(std::ofstream& file) const;
    void loadAchievements(std::ifstream& file);
    void displayAchievements() const;
};
