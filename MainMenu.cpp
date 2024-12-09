#include "MainMenu.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void Menu::savePlayerData() {
    // Construct file path
    std::string fileName = "./players/" + player->getName() + ".json";

    // Check if file exists by attempting to open it
    std::ifstream fileCheck(fileName);
    if (!fileCheck.good()) {
        // File does not exist, so create a new JSON structure
        json playerData = {
            {"name", player->getName()},
            {"wordle", {{"gamesPlayed", 0}, {"gamesWon", 0}, {"totalTime", 0}}},
            {"hangman", {{"gamesPlayed", 0}, {"gamesWon", 0}, {"totalTime", 0}}},
            {"snake", {{"highestScore", 0}}}
        };

        // Write JSON to file
        std::ofstream outFile(fileName);
        outFile << playerData.dump(4);  
        outFile.close();
    }
    else {
        // File exists, load existing data
        json playerData;
        fileCheck >> playerData;
        fileCheck.close();
        std::cout << "Loaded existing player data for: " << playerData["name"] << std::endl;
    }
}

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
    // Title Text ("Nintendo Game")
    titleText.setFont(font);
    titleText.setString("Nintendo Game");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Black);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(800 / 2, 50); // Centered at the top

    // Subtitle Text ("Main Menu")
    subtitleText.setFont(font);
    subtitleText.setString("Main Menu");
    subtitleText.setCharacterSize(24);
    subtitleText.setFillColor(sf::Color::Black);
    sf::FloatRect subtitleBounds = subtitleText.getLocalBounds();
    subtitleText.setOrigin(subtitleBounds.width / 2, subtitleBounds.height / 2);
    subtitleText.setPosition(800 / 2, 100);

    // Sign In Button
    signInButton.setSize({ 150, 50 });
    signInButton.setPosition(650, 10);  // Top-right corner
    signInButton.setFillColor(sf::Color::Blue);

    signInButtonText.setFont(font);
    signInButtonText.setString("Sign In");
    signInButtonText.setCharacterSize(20);
    signInButtonText.setFillColor(sf::Color::White);
    signInButtonText.setPosition(signInButton.getPosition().x + 20, signInButton.getPosition().y + 10);

    // Popup
    popupBox.setSize({ 400, 200 });
    popupBox.setFillColor(sf::Color(50, 50, 50, 240));
    popupBox.setOrigin(200, 100);  // Center for scaling
    popupBox.setPosition(400, 300);  // Center of the window

    popupTitle.setFont(font);
    popupTitle.setString("Enter the Name of the User");
    popupTitle.setCharacterSize(24);
    popupTitle.setFillColor(sf::Color::White);
    popupTitle.setPosition(popupBox.getPosition().x - 180, popupBox.getPosition().y - 60);

    userInputText.setFont(font);
    userInputText.setString("");
    userInputText.setCharacterSize(20);
    userInputText.setFillColor(sf::Color::White);
    userInputText.setPosition(popupBox.getPosition().x - 180, popupBox.getPosition().y - 20);

    popupSignInButton.setSize({ 100, 40 });
    popupSignInButton.setPosition(popupBox.getPosition().x + 50, popupBox.getPosition().y + 50);
    popupSignInButton.setFillColor(sf::Color::Green);

    popupSignInButtonText.setFont(font);
    popupSignInButtonText.setString("Sign In");
    popupSignInButtonText.setCharacterSize(18);
    popupSignInButtonText.setFillColor(sf::Color::White);
    popupSignInButtonText.setPosition(popupSignInButton.getPosition().x + 20, popupSignInButton.getPosition().y + 10);

    // Load cursors
    if (!defaultCursor.loadFromSystem(sf::Cursor::Arrow)) {
        std::cout << "Error loading default cursor" << std::endl;
    }
    if (!pointerCursor.loadFromSystem(sf::Cursor::Hand)) {
        std::cout << "Error loading pointer cursor" << std::endl;
    }

}

Menu::~Menu()
{
    if (player) delete player;

}

void Menu::handleInput(sf::Event& event, sf::RenderWindow* window) {
    if (signInPopup) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !userInputText.getString().isEmpty()) {
                std::string currentText = userInputText.getString();
                currentText.pop_back();
                userInputText.setString(currentText);
            }
            else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                userInputText.setString(userInputText.getString() + static_cast<char>(event.text.unicode));
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            if (popupSignInButton.getGlobalBounds().contains(mousePos)) {
                // Create Player
                player = new Player(userInputText.getString());

                // Save or Load Player Data
                savePlayerData();

                signInPopup = false;
                popupGrowing = false;
            }
        }
    }
    else {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            if (signInButton.getGlobalBounds().contains(mousePos)) {
                signInPopup = true;
                popupGrowing = true;
            }
        }
    }
}

Player* Menu::getCurrentPlayer()
{
    return player;
}

int Menu::checkClick(sf::RenderWindow& window)
{
    // Get mouse position as two integers
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));


    for (int i = 0; i < 3; ++i) {
        // Check if the mouse position is within the bounds of any menu option
        if (gameOptionsBoundaries[i].contains(mousePos)) {
            return i;
        }
    }
    return -1;
}

void Menu::render(sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool hovering = false;
    // Draw Background
    window.draw(backgroundSprite);

    // Draw Title and Subtitle
    window.draw(titleText);
    window.draw(subtitleText);

    // Draw Menu Options
    for (int i = 0; i < 3; ++i) {
        sf::Text text(menuOptions[i], font, 30);
        text.setPosition(355 - i * 10, 220 + i * 45);
        text.setFillColor(sf::Color::Black);
        gameOptionsBoundaries[i] = text.getGlobalBounds();

        // Check if hovering over text
        if (gameOptionsBoundaries[i].contains(mousePos)) {
            hovering = true; // Set hover flag
            text.setFillColor(sf::Color::Red); // Optional hover effect
        }

        window.draw(text);
    }

    // Draw Sign In Button or Player Name
    if (player) {
        sf::Text playerName(player->getName(), font, 20);
        playerName.setPosition(650, 10);
        playerName.setFillColor(sf::Color::Black);

        // Hover check for player name
        if (playerName.getGlobalBounds().contains(mousePos)) {
            hovering = true; // Set hover flag
        }

        window.draw(playerName);
    }
    else {
        // Hover check for main Sign In Button
        if (signInButton.getGlobalBounds().contains(mousePos)) {
            hovering = true; // Set hover flag
        }
        window.draw(signInButton);
        window.draw(signInButtonText);
    }

    // Draw Popup if Active
    if (signInPopup) {
        if (popupGrowing && popupScale < 1.0f) {
            popupScale += 0.05f;  // Smooth scaling
            popupBox.setScale(popupScale, popupScale);
        }
        else if (!popupGrowing && popupScale > 0.0f) {
            popupScale -= 0.05f;
            popupBox.setScale(popupScale, popupScale);
        }

        window.draw(popupBox);
        window.draw(popupTitle);
        window.draw(userInputText);
        window.draw(popupSignInButton);
        window.draw(popupSignInButtonText);

        // Hover check for popup Sign In Button
        if (popupSignInButton.getGlobalBounds().contains(mousePos)) {
            hovering = true; // Set hover flag
        }

    }


    // Update Cursor
    if (hovering && !isPointer) {
        window.setMouseCursor(pointerCursor); // Set pointer cursor
        isPointer = true;
    }
    else if (!hovering && isPointer) {
        window.setMouseCursor(defaultCursor); // Revert to default cursor
        isPointer = false;
    }


}
