#include "PauseResumeHandler.h"
#include <iostream>

PauseResumeHandler::PauseResumeHandler(const sf::Vector2f& buttonSize, const sf::Font& font)
    : gamePaused(false),
    pauseButton(buttonSize, sf::Vector2f(50.f, 10.f), "Pause", "./assets/fonts/font1.ttf"), // Use a string for the font path
    resumeButton(buttonSize, sf::Vector2f(50.f, 10.f), "Resume", "./assets/fonts/font1.ttf") { // Use the same font path
    // Set the position for the buttons if needed, already set by the constructor
    pauseButton.setPosition(sf::Vector2f(700.f, 550.f));
    resumeButton.setPosition(sf::Vector2f(700.f, 549.f)); // Adjust position to avoid overlap
}


void PauseResumeHandler::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button != sf::Mouse::Left) return;

        // Map mouse position to the coordinate system of the window
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (pauseButton.getGlobalBounds().contains(mousePos) && !gamePaused) {
            std::cout << "Pause button clicked. Pausing game." << std::endl;
            gamePaused = true;
            return; // Exit after handling the pause action
        }

        if (resumeButton.getGlobalBounds().contains(mousePos) && gamePaused) {
            std::cout << "Resume button clicked. Resuming game." << std::endl;
            gamePaused = false;
            return; // Exit after handling the resume action
        }
    }
}


void PauseResumeHandler::draw(sf::RenderWindow& window) {
    if (gamePaused) {
        resumeButton.draw(window); // Draw the resume button if the game is paused
    }
    else {
        pauseButton.draw(window); // Draw the pause button if the game is running
    }
}

bool PauseResumeHandler::isGamePaused() const {
    return gamePaused;
}
