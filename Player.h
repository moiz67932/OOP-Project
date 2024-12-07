#pragma once
#include <string>
#include "AchievementSystem.h"
using namespace std;

class Player {
private:
    string name;
    int id;
    AchievementSystem achievements;

public:
    Player(const string& name, int id);

    string getName();
    int getId();

    void updateAchievement(const string& game, int score);
    void saveProgress() const;
    void loadProgress();

    void displayProgress() const;
};
