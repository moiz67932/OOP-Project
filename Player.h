#pragma once
#include <string>
#include "AchievementSystem.h"
using namespace std;

class Player {
private:
    string name;
    AchievementSystem achievements;
public:
    Player(const string& name);

    string getName();

    void updateAchievement(const string& game, int score);
    void saveProgress() const;
    void loadProgress();

    void displayProgress() const;
};
