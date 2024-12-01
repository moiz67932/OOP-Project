//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include<iostream>
//#include "MainMenu.h"
//#include "Snake.h"
//#include "Wordle.h"
//#include "Hangman.h"
//
//
//class Screen {
//private:
//    int resolutionX;
//    int resolutionY;
//    sf::RenderWindow* window;
//    Game* currentState;
//
//public:
//    Screen(int x, int y);
//    ~Screen();
//
//    void manageState(Menu* menu, Snake* snake, Wordle* wordle, Hangman* hangman);
//    void renderCurrentState();
//};



#include <SFML/Graphics.hpp>
#include "MainMenu.h"  // Include your menu class
#include "Snake.h"      // Include your Snake game class
#include "Wordle.h"     // Include your Wordle game class
#include "Hangman.h"    // Include your Hangman game class


class Screen {
public:
    // Constructor to initialize the SFML window with resolution
    Screen(int resolutionX, int resolutionY);

    // Destructor to clean up the window and any allocated resources
    ~Screen();

    // Function to manage state transitions and render the current state
    void manageState(Menu* menu, Snake* snake, Wordle* wordle, Hangman* hangman);

    // Renders the current active state (menu or game)
    void renderCurrentState(sf::RenderWindow& window);

private:
    sf::RenderWindow* window;  // SFML window for rendering
    Game* gameState;        // Pointer to the current Game
    Menu* menuState;        // Pointer to Menu
};