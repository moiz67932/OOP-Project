#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::Color normalColor;
    sf::Color hoverColor;
    bool isHovered;


public:
    // Constructor
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const string& buttonText, const string& fontPath);

    // Draw the button
    void draw(sf::RenderWindow& window);

    // Handle events for hover and click detection
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    // Check if the button is being hovered over
    bool isButtonHovered() const;

    // Set the position of the button
    void setPosition(const sf::Vector2f& position);

    sf::FloatRect getGlobalBounds() const;
};
