#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Button {
private:
    sf::RectangleShape shape;
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::Text text;
    sf::Font font;
    sf::Color normalColor;
    sf::Color hoverColor;
    bool isHovered;

public:
    // Constructor
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const string& buttonText, const string& fontPath, const string& buttonTexturePath);

    // Draw the button
    void draw(sf::RenderWindow& window);

    // Handle events for hover and click detection
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    // Check if the button is being hovered over
    bool isButtonHovered() const;

    void setPosition(const sf::Vector2f& position);

};

#endif // BUTTON_H
