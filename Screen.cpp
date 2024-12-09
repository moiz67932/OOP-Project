#include "Screen.h"
#include "SoundSystem.h"


// Constructor 
Screen::Screen(int resolutionX, int resolutionY) {
    window = new sf::RenderWindow(sf::VideoMode(resolutionX, resolutionY), "GameBoy Screen");
    gameState = nullptr; 
    menuState = nullptr;
    soundSystem = nullptr;
}

// Destructor
Screen::~Screen() {
    delete window;
}

void Screen::setSoundSystem(SoundSystem* currentsoundSystem)
{
    this->soundSystem = currentsoundSystem;
    this->soundSystem->initMusic("./assets/music/music.mp3", "./assets/music/music.mp3");

}

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

                soundSystem->handleInput(event);
                soundSystem->updateMusicState();
            


            // Handle Events on the menu
            if (menuState == menu &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                int clickedOption = menu->checkClick(*window);
                if (clickedOption == 0)
                { // Start Snake Game
                    gameState = snake;
                    snake->startGame(); // Ensure the snake game is reset
                    menuState = nullptr;
                }

                else if (clickedOption == 1) {  
                    gameState = wordle;
                    wordle->setPlayer(menu->getCurrentPlayer());
                    wordle->startGame();
                    menuState = nullptr;
                }
                else if (clickedOption == 2) {  
                    gameState = hangman;
                    hangman->setPlayer(menu->getCurrentPlayer());
                    hangman->startGame(); 
                    menuState = nullptr;
                }
                else {
                menuState = menu;
                }
            }


            // Pass input events to the current game
            /*if (gameState == snake) {
                if (event.type == sf::Event::TextEntered ||
                    event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::MouseButtonPressed) {
                    snake->handleInput(event);
                    snake->updateGame();
                }
            }*/

            // Handle input and update for SnakeGame
            if (gameState == snake)
            {
                if (event.type == sf::Event::TextEntered || event.type == sf::Event::KeyPressed)
                {
                    snake->handleInput(event);  // Handle Snake Input
                    snake->updateGame();
                }
            }


            // Pass input events to the current game
            if (gameState == wordle) {
                if (event.type == sf::Event::TextEntered ||
                    event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::MouseButtonPressed) {
                    wordle->handleInput(event,window);
                }
            }

            // Pass input events to the current game
            if (gameState == hangman && hangman != nullptr) {
                if (event.type == sf::Event::TextEntered ||
                    event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::MouseButtonPressed) {
                    hangman->handleInput(event, *window);
                }
            }

            if (menuState == menu) {
                if (event.type == sf::Event::TextEntered ||
                    event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::MouseButtonPressed) {
                    menu->handleInput(event,window);
                }
            }
            // Check if Wordle wants to return to menu
            if (gameState == wordle && wordle != nullptr && wordle->shouldReturnToMenu) {
                //gameState = nullptr;
                menuState = menu;
                wordle->shouldReturnToMenu = false;
                //wordle->resetGame();  // Reset the game state
                break;  // Break the inner event loop to restart
            }

            // Check if Wordle wants to return to menu
            if (gameState == hangman && hangman != nullptr && hangman->shouldReturnToMenu) {
                //gameState = nullptr;
                menuState = menu;
                hangman->shouldReturnToMenu = false;
                //wordle->resetGame();  // Reset the game state
                break;  // Break the inner event loop to restart
            }
        }

        // Render the current state
        renderCurrentState(*window);
        soundSystem->render(*window);
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
