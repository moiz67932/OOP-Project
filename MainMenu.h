#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

class Menu {
private:
    string menuOptions[3];
    sf::FloatRect gameOptionsBoundaries[3];
    sf::Font font;
    sf::Texture backgroundTexture;  
    sf::Sprite backgroundSprite;

    //Cursor
    sf::Cursor defaultCursor;
    sf::Cursor pointerCursor;
    bool isPointer = false;

    sf::RectangleShape signInButton;
    sf::Text signInButtonText;

    // Popup
    bool signInPopup;
    sf::RectangleShape popupBox;
    sf::Text popupTitle;
    sf::Text userInputText;
    sf::RectangleShape popupSignInButton;
    sf::Text popupSignInButtonText;
    sf::Text titleText;
    sf::Text subtitleText;

    float popupScale;
    bool popupGrowing;

    Player* player;  // Player object to store user info

    // Private Functions
    void loadFont();
    void loadBackground();
    void savePlayerData();
public:
    Menu();
    ~Menu();
    int checkClick(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void handleInput(sf::Event& event, sf::RenderWindow* window);

    // Get Current Player
    Player* getCurrentPlayer();

};