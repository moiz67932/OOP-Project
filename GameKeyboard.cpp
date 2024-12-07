#include"GameKeyboard.h"

// Constructor
GameKeyboard::GameKeyboard() {
    for (int i = 0; i < 26; i++) {
        keyColors[i] = sf::Color(180, 180, 180, 255);
    }

    // Font
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        std::cerr << "Keyboard Font Loading Error" << std::endl;
    }

    initializeKeyboardDisplay();
}

// Keyboard display
void GameKeyboard::initializeKeyboardDisplay() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < MAX_KEYS_PER_ROW; col++) {
            char currentKey = keyboardLayout[row][col];
            if (currentKey == '\0') continue;

            int index = currentKey - 'A';

            // Create a box for the key
            keyboardBoxes[index].setSize(sf::Vector2f(KEY_WIDTH, KEY_HEIGHT));
            keyboardBoxes[index].setFillColor(keyColors[index]);
            keyboardBoxes[index].setOutlineColor(sf::Color::Black);
            keyboardBoxes[index].setOutlineThickness(2.f);

            // Position the box
            double xOffset = (row == 0) ? 0 :
                (row == 1) ? KEY_WIDTH / 2 + 6.0 :
                KEY_WIDTH + 20.0;

            keyboardBoxes[index].setPosition(
                START_POSITION.x + col * (KEY_WIDTH + KEY_SPACING) + xOffset,
                START_POSITION.y + row * (KEY_HEIGHT + KEY_SPACING)
            );

            // Create the text for the key
            keyboardTexts[index].setFont(font);
            keyboardTexts[index].setString(std::string(1, currentKey));
            keyboardTexts[index].setCharacterSize(20);
            keyboardTexts[index].setFillColor(sf::Color::Black);

            // Center the text within the key
            sf::FloatRect textBounds = keyboardTexts[index].getLocalBounds();
            keyboardTexts[index].setOrigin(
                textBounds.left + textBounds.width / 2.0f,
                textBounds.top + textBounds.height / 2.0f
            );
            keyboardTexts[index].setPosition(
                keyboardBoxes[index].getPosition().x + KEY_WIDTH / 2,
                keyboardBoxes[index].getPosition().y + KEY_HEIGHT / 2
            );
        }
    }
}

// Change the color of a specific key
void GameKeyboard::changeLetterColor(char letter, sf::Color color) {
    // Convert to uppercase
    letter = std::toupper(letter);

    // Validate the letter
    if (letter < 'A' || letter > 'Z') return;

    // Calculate index
    int index = letter - 'A';

    // Define color priority
    // Green has the highest priority
    if (color == sf::Color::Green) {
        keyColors[index] = color;
        keyboardBoxes[index].setFillColor(color);
        return;
    }

    // Yellow has medium priority
    if (color == sf::Color::Yellow) {
        // Only change if current color is not Green
        if (keyColors[index] != sf::Color::Green) {
            keyColors[index] = color;
            keyboardBoxes[index].setFillColor(color);
        }
        return;
    }

    // Grey has the lowest priority
    if (color == sf::Color(100, 100, 100)) {
        // Only change if current color is neither Green nor Yellow
        if (keyColors[index] != sf::Color::Green &&
            keyColors[index] != sf::Color::Yellow) {
            keyColors[index] = color;
            keyboardBoxes[index].setFillColor(color);
        }
    }
}

// Render the keyboard
void GameKeyboard::render(sf::RenderWindow& window) {
    for (int i = 0; i < 26; i++) {
        if (keyboardTexts[i].getString().isEmpty()) continue;

        window.draw(keyboardBoxes[i]);
        window.draw(keyboardTexts[i]);
    }
}

// Reset the keyboard colors to default
void GameKeyboard::resetKeyboard() {
    for (int i = 0; i < 26; i++) {
        keyColors[i] = sf::Color(180, 180, 180, 255);
        keyboardBoxes[i].setFillColor(keyColors[i]);
    }
}
