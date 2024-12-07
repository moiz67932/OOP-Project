#include "Player.h"
#include <iostream>
#include <fstream>
using namespace std;

Player::Player(const string& name, int id) {
    this->name = name;
    this->id = id;
}

string Player::getName() { 
    return name; 
}

int Player::getId() { 
    return id;
}

void Player::updateAchievement(const string& game, int score) {
    achievements.updateAchievement(game, score);
}

void Player::saveProgress() const {
    ofstream file("player_" + to_string(id) + ".txt");
    if (file.is_open()) {
        file << name << "\n" << id << "\n";
        achievements.saveAchievements(file);
        file.close();
    }
}

void Player::loadProgress() {
    ifstream file("player_" + to_string(id) + ".txt");
    if (file.is_open()) {
        getline(file, name);
        file >> id;
        achievements.loadAchievements(file);
        file.close();
    }
}

void Player::displayProgress() const {
    cout << "Player: " << name << " (ID: " << id << ")\n";
    achievements.displayAchievements();
}
