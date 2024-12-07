#pragma once
#include "Player.h"
#include <iostream>

class Leaderboard {
private:
	int highscore[100];
	Player topPlayers[10];

public:
	void updateScore(Player player, int score);
	void displayTopScores();
	void resetLeaderboard();
	void saveLeaderboard();
	void loadLeaderboard();

};
