//#include "Game.h"
//
//void Game::loadFont()
//{
//    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
//        cout << "Font Loading Error :: MainMenu.cpp" << endl;
//    }
//}
//
//void Game::loadBackground()
//{
//    // Load the background texture
//    if (!backgroundTexture.loadFromFile("./assets/images/Wordle.png")) {
//        cout << "Background Loading Error :: Game.cpp" << endl;
//    }
//    backgroundSprite.setTexture(backgroundTexture);
//}
//
//Game::Game()
//{
//    // Load Font and Background
//    loadFont();
//    loadBackground();
//}
//
//void Game::display(sf::RenderWindow& window)
//{
//    // Draw Background
//    window.draw(backgroundSprite);
//}
