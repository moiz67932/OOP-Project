#include "MainMenu.h"

void Menu::loadFont()
{
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        cout << "Font Loading Error :: MainMenu.cpp" << endl;
    }
}

void Menu::loadBackground()
{
    // Load the background texture
    if (!backgroundTexture.loadFromFile("./assets/images/background.jpg")) {
        cout << "Background Loading Error :: Menu.cpp" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

Menu::Menu() {
    menuOptions[0] = "Snake";
    menuOptions[1] = "Wordle";
    menuOptions[2] = "Hangman";

    // Load Font and Background
    loadFont();
    loadBackground();
}

int Menu::checkClick(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    for (int i = 0; i < 3; ++i) {
        if (gameOptionsBoundaries[i].contains(static_cast<sf::Vector2f>(mousePosition))) {
            return i; 
        }
    }
    return -1;
}

void Menu::render(sf::RenderWindow& window) {
    // Draw Background
    window.draw(backgroundSprite); 

    // Draw Menu Options
    for (int i = 0; i < 3; ++i) {  
        sf::Text text(menuOptions[i], font, 30);
        text.setPosition(355 - i*10, 220 + i * 45);
        text.setFillColor(sf::Color::Black);

        gameOptionsBoundaries[i] = text.getGlobalBounds();

        window.draw(text);
    }

}
