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
    sf::Clock clock; // Add a clock to track time for updates
    const int frameTime = 100; // Milliseconds per frame (can align with snake's speed)


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
                if (clickedOption == 0) {  
                    gameState = snake;
                    snake->startGame();  
                }
                else if (clickedOption == 1) {  
                    gameState = wordle;
                    wordle->startGame();
                }
                else if (clickedOption == 2) {  
                    gameState = hangman;
                    hangman->startGame(); 
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

            // Pass input events to the current game
            if (gameState == hangman && hangman != nullptr) {
                if (event.type == sf::Event::TextEntered ||
                    event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::MouseButtonPressed) {
                    hangman->handleInput(event);
                }
            }

            // Pass input events to the current game
            //if (gameState == snake && snake != nullptr) {
            //    if (event.type == sf::Event::TextEntered ||
            //        event.type == sf::Event::KeyPressed ||
            //        event.type == sf::Event::MouseButtonPressed) {
            //        snake->handleInput(event);
            //    }
            //}

                    // Handle game logic updates based on timer
            if (gameState == snake && clock.getElapsedTime().asMilliseconds() >= frameTime) {
                snake->handleInput(event);
                snake->updateGame();
                clock.restart(); // Reset the clock for the next update
            }



            // Check if Wordle wants to return to menu
            //if (gameState == wordle && wordle != nullptr  && wordle->shouldReturnToMenu) {
            //    //gameState = nullptr;
            //    menuState = menu;
            //    wordle->shouldReturnToMenu = false;
            //    gameState = nullptr;
            //    //wordle->resetGame();  // Reset the game state
            //    break;  // Break the inner event loop to restart
            //}
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
