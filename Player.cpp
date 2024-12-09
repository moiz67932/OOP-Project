#include "Player.h"
#include <iostream>
#include <fstream>
using namespace std;


Player::Player(const string& name) {
    this->name = name;
}

string Player::getName() { 
    return name; 
}

void Player::updateAchievement(const string& game, int score) {
    achievements.updateAchievement(game, score);
}

void Player::saveProgress() const {
    ofstream file("player_" + name + ".txt");
    if (file.is_open()) {
        file << name << "\n";
        achievements.saveAchievements(file);
        file.close();
    }
}

void Player::loadProgress() {
    ifstream file("player_" + name + ".txt");
    if (file.is_open()) {
        getline(file, name);
        file >> name;
        achievements.loadAchievements(file);
        file.close();
    }
}

void Player::displayProgress() const {
    cout << "Player: " << name << "\n";
    achievements.displayAchievements();
}
