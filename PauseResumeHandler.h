#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class PauseResumeHandler {
private:
    bool gamePaused;
    Button pauseButton;
    Button resumeButton;

public:
    // Constructor
    PauseResumeHandler(const sf::Vector2f& buttonSize, const sf::Font& font);

    // Handle events for pause and resume buttons
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    // Draw the appropriate button based on the game state
    void draw(sf::RenderWindow& window);

    // Check if the game is paused
    bool isGamePaused() const;
};
