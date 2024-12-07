#pragma once

#include "Screen.h"
#include "SoundSystem.h"
#include "MainMenu.h"
#include "Leaderboard.h"
#include "Snake.h"
#include "Wordle.h"
#include "Hangman.h"

class GameBoy {
private:
    Screen* screen;
    SoundSystem* soundSystem;
    Menu menu;
    Snake snakeGame;
    Wordle wordleGame;
    Hangman hangmanGame;

public:
    GameBoy();
    ~GameBoy();

    void start();
};