//#include "Screen.h"
//
//Screen::Screen(int x, int y) : resolutionX(x), resolutionY(y) {
//    // Create an SFML window with the given resolution
//    window = new sf::RenderWindow(sf::VideoMode(resolutionX, resolutionY), "GameBoy Screen");
//}
//
//Screen::~Screen() {
//    // Close and clean up the SFML window
//    //window->close();
//    delete window;
//}
//
//void Screen::manageState()
//{
//}
//
//// Render Menu
//void Screen::render(Menu* menu) {
//    menu->display(*window);
//}
//
//// Render Game
//void Screen::render(Game* game) {
//    game->display(*window);
//}
//
//// Main loop 
//void Screen::render(Menu* menu, Game* game) {
//    void* activeScreen = menu; // Start with the menu
//
//    // Main loop to keep the window open
//    while (window->isOpen()) {
//        sf::Event event;
//        while (window->pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window->close();
//
        //    // Handle click events when on the menu
        //    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        //        if (activeScreen == menu) { 
        //            int clickedOption = menu->checkClick(*window);
        //            if (clickedOption == 1) { 
        //                activeScreen = game; 
        //            }
        //        }
        //    }
        //}
//
//        window->clear();
//
//        // Render Menu
//        if (activeScreen == menu) {
//            render(menu); 
//        }
//        else if (activeScreen == game) {
//            render(game);
//        }
//
//        window->display();
//    }
//}
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor initializes the SFML window
Screen::Screen(int resolutionX, int resolutionY) {
    window = new sf::RenderWindow(sf::VideoMode(resolutionX, resolutionY), "GameBoy Screen");
    gameState = nullptr;  // Initially no state
    menuState = nullptr;  // Initially no state
}

// Destructor to clean up the dynamically allocated window
Screen::~Screen() {
    delete window;
}

// Manages state transitions and renders the active state
//void Screen::manageState(Menu* menu, Snake* snake, Wordle* wordle, Hangman* hangman) {
//    // Set the initial state to the menu
//    if (!gameState) {
//        menuState = menu;
//    }
//
//    while (window->isOpen()) {
//        sf::Event event;
//        while (window->pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window->close();
//            }
//
//            // Handle click events when on the menu
//            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//                if (menuState == menu) {
//                    int clickedOption = menu->checkClick(*window);
//                    if (clickedOption == 0) {  // "Snake" clicked
//                        gameState = snake;
//                        snake->startGame();  // Initialize Snake game
//                    }
//                    else if (clickedOption == 1) {  // "Wordle" clicked
//                        gameState = wordle;
//                        wordle->startGame();  // Initialize Wordle game
//                    }
//                    else if (clickedOption == 2) {  // "Hangman" clicked
//                        gameState = hangman;
//                        hangman->startGame();  // Initialize Hangman game
//                    }
//                }
//            }
//
//            // Pass input events to the current game when it's active
//            if (gameState == wordle && event.type == sf::Event::TextEntered) {
//                wordle->handleInput(event);
//            }
//            else if (gameState == wordle && event.type == sf::Event::KeyPressed) {
//                wordle->handleInput(event);
//            }
//            else if (gameState == wordle && event.type == sf::Event::MouseButtonPressed) {
//                wordle->handleInput(event);
//            }
//            // Check if Wordle wants to return to menu
//            if (gameState == wordle && wordle->shouldReturnToMenu) {
//                gameState = nullptr;
//                wordle->shouldReturnToMenu = false;
//                break;  // Exit the game loop to reset game states
//            }
//        }
//
//        // Render the active state
//        renderCurrentState(*window);
//    }
//}

void Screen::manageState(Menu* menu, Snake* snake, Wordle* wordle, Hangman* hangman) {
    // Set the initial state to the menu
    if (!gameState) {
        menuState = menu;
    }

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }

            // Handle click events when on the menu
            if (menuState == menu &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                int clickedOption = menu->checkClick(*window);
                if (clickedOption == 0) {  // "Snake" clicked
                    gameState = snake;
                    snake->startGame();  // Initialize Snake game
                }
                else if (clickedOption == 1) {  // "Wordle" clicked
                    gameState = wordle;
                    wordle->startGame();  // Initialize Wordle game
                }
                else if (clickedOption == 2) {  // "Hangman" clicked
                    gameState = hangman;
                    hangman->startGame();  // Initialize Hangman game
                }
                menuState = nullptr;
            }

            // Pass input events to the current game
            if (gameState == wordle && wordle != nullptr) {
                if (event.type == sf::Event::TextEntered ||
                    event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::MouseButtonPressed) {
                    wordle->handleInput(event);
                }
            }

            // Check if Wordle wants to return to menu
            if (gameState == wordle && wordle != nullptr  && wordle->shouldReturnToMenu) {
                //gameState = nullptr;
                menuState = menu;
                wordle->shouldReturnToMenu = false;
                //wordle->resetGame();  // Reset the game state
                break;  // Break the inner event loop to restart
            }
        }

        // Render the current state
        renderCurrentState(*window);
    }
}
// Renders the current state
void Screen::renderCurrentState(sf::RenderWindow& window) {
    window.clear();

    if (gameState != nullptr) {
        gameState->render(window);
    }
    if (menuState!=nullptr)
        menuState->render(window);

    window.display();
}
