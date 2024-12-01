#pragma once

#include "Screen.h"
#include "MainMenu.h"
#include "Snake.h"
#include "Wordle.h"
#include "Hangman.h"

class GameBoy {
private:
    Screen* screen;
    Menu menu;
    Snake snakeGame;
    Wordle wordleGame;
    Hangman hangmanGame;

public:
    GameBoy();
    ~GameBoy();

    void start();
};