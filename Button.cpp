#include "Button.h"
using namespace std;

// Constructor: Initialize button shape, text, and load font
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const string& buttonText, const string& fontPath, const string& buttonTexturePath) {
    if (!font.loadFromFile(fontPath)) {
        // Handle error if the font fails to load
    }

    //Load Button Texture
    buttonTexture.loadFromFile(buttonTexturePath);
    buttonSprite.setTexture(buttonTexture);
    // Set texture origin to the center
    sf::FloatRect textureBounds = buttonSprite.getLocalBounds();
    buttonSprite.setOrigin(textureBounds.width / 2.0f, textureBounds.height / 2.0f);
    buttonSprite.setPosition(position);

    // Configure the button shape
    shape.setSize(size);
    shape.setPosition(position);
    normalColor = sf::Color(200, 200, 200); // Default color
    hoverColor = sf::Color(150, 150, 150);  // Hover color
    shape.setFillColor(normalColor);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    // Configure the button text
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Center the text within the button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f-10.0);

    isHovered = false;
}

// Draw the button on the window
void Button::draw(sf::RenderWindow& window) {
    window.draw(buttonSprite);
    window.draw(text);
}

// Handle events to check if the button is hovered or clicked
void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool contains = shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (contains) {
        shape.setFillColor(hoverColor);
        isHovered = true;
    }
    else {
        shape.setFillColor(normalColor);
        isHovered = false;
    }

    // Handle click event if the button is hovered over
    if (contains && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Perform click action (add custom action here if needed)
    }
}

// Return whether the button is currently hovered
bool Button::isButtonHovered() const {
    return isHovered;
}
