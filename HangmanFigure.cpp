#include "HangmanFigure.h"

HangmanFigure::HangmanFigure() : fadeSpeed(0.02f) { // Set a default fade speed
    for (int i = 0; i < maxIncorrectAttempts; ++i) {
        opacity[i] = 0; // Initialize opacity to 0 (fully transparent)
    }
}

HangmanFigure::~HangmanFigure() {
    // Destructor: cleanup if needed
}

void HangmanFigure::loadTextures(const std::string& basePath) {
    for (int i = 0; i < maxIncorrectAttempts; ++i) {
        std::string filePath = basePath + std::to_string(i + 1) + ".jpg";
        if (!textures[i].loadFromFile(filePath)) {
            std::cout << "Error loading texture: " << filePath << std::endl;
        }
        else {
            sprites[i].setTexture(textures[i]);
            sprites[i].setPosition(229.f, 205.f); // Adjust this position as needed
        }
    }
}

void HangmanFigure::draw(sf::RenderWindow& window, int incorrectAttempts) {
    // Check if it's time to increment the opacity
    if (fadeClock.getElapsedTime().asSeconds() > fadeSpeed) {
        fadeClock.restart(); // Reset the timer

        // Gradually increase the opacity for each sprite that should be shown
        for (int i = 0; i < incorrectAttempts && i < maxIncorrectAttempts; ++i) {
            if (opacity[i] < 255) {
                opacity[i] += 5; // Increment opacity (adjust this value for faster/slower fades)
                if (opacity[i] > 255) {
                    opacity[i] = 255; // Cap opacity to 255 (fully opaque)
                }
                sprites[i].setColor(sf::Color(255, 255, 255, opacity[i]));
            }
        }
    }

    // Draw the sprites with their updated opacity
    for (int i = 0; i < incorrectAttempts && i < maxIncorrectAttempts; ++i) {
        window.draw(sprites[i]);
    }
}
