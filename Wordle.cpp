#include "Wordle.h"
using namespace std;

void Wordle::loadFont()
{
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        cout << "Font Loading Error :: MainMenu.cpp" << endl;
    }
}

void Wordle::loadBackground()
{
    // Load the background texture
    if (!backgroundTexture.loadFromFile("./assets/images/backgroundWordle.jpg")) {
        cout << "Background Loading Error :: Game.cpp" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

Wordle::Wordle():pauseResumeHandler(sf::Vector2f(100.f, 50.f), font){
    cout << "Wordle Game Initialized!" << endl;

    // Reset game state
    currentRow = 0;
    currentColumn = 0;
    gameWon = false;
    // Message Reset
    messageText.setString(' ');
    shouldReturnToMenu = false;
    currentPlayer = nullptr;
    showMessage = false;
    windowPtr = nullptr;


    // Initialize Back Button
    shouldReturnToMenu = false;
    backButton.setSize(sf::Vector2f(100, 40));
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(20.f, 20.f);  // Top-left corner

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(20);
    backButtonText.setFillColor(sf::Color::White);

    // Center the text on the button
    sf::FloatRect textBounds = backButtonText.getLocalBounds();
    backButtonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    backButtonText.setPosition(
        backButton.getPosition().x + backButton.getSize().x / 3.6f,
        backButton.getPosition().y + backButton.getSize().y / 1.5f
    );

    // Leaderboard Text
    leaderboardText.setFont(font);
    leaderboardText.setString("Leaderboard");
    leaderboardText.setCharacterSize(20);
    leaderboardText.setFillColor(sf::Color::Black);
    leaderboardText.setPosition(650, playerNameBorder.getPosition().y + 80);

}

Wordle::~Wordle() {
    cout << "Wordle Game Destroyed!" << endl;
}

void Wordle::startGame() {
    cout << "Starting Wordle Game!" << endl;
    // Initialize resources for Wordle game
    loadFont();
    loadBackground();
    selectRandomWord();
    resetGame();
}

void Wordle::endGame() {
    cout << "Ending Wordle Game!" << endl;
}

void Wordle::resetGame() {
    // Reset the grid
    initializeGrid();
    keyboard.resetKeyboard();

    // Select a new random word
    selectRandomWord();


    // Reset game state
    currentRow = 0;
    currentColumn = 0;
    gameWon = false;

    // Message Reset
    messageText.setString(' ');
    shouldReturnToMenu = false;
    gameTimer.restart(); // Reset the game timer

}

void Wordle::initializeGrid() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            letterGrid[i][j].reset();
        }
    }
}

void Wordle::selectRandomWord() {
    dictionary.getRandomWord(targetWord);
}

void Wordle::checkWord() {
    // Check if the word is complete
    if (currentColumn < 5) {
        // Create a message text
        messageText.setFont(font);
        messageText.setString("Complete the Word");
        messageText.setCharacterSize(24);
        messageText.setFillColor(sf::Color::Red);
        messageText.setPosition(280.f, 20.f);
        return;
    }

    // Create a copy of the target word to track matched letters
    //char tempTargetWord[6];
    string tempTargetWord = targetWord;
    //strcpy(tempTargetWord, targetWord);

    // Exact Match
    for (int j = 0; j < 5; j++) {
        if (letterGrid[currentRow][j].getCharacter() == tempTargetWord[j]) {
            letterGrid[currentRow][j].setBackgroundColor(sf::Color::Green);
            keyboard.changeLetterColor(letterGrid[currentRow][j].getCharacter(), sf::Color::Green);
            letterGrid[currentRow][j].reveal();
            tempTargetWord[j] = '*';  
        }
    }

    // Exists but is in Wrong Position
    for (int j = 0; j < 5; j++) {
        if (letterGrid[currentRow][j].getBackgroundColor() != sf::Color::Green) {
            bool found = false;
            for (int k = 0; k < 5; k++) {
                if (letterGrid[currentRow][j].getCharacter() == tempTargetWord[k] && tempTargetWord[k] != '*') {
                    letterGrid[currentRow][j].setBackgroundColor(sf::Color::Yellow);
                    keyboard.changeLetterColor(letterGrid[currentRow][j].getCharacter(), sf::Color::Yellow);
                    letterGrid[currentRow][j].reveal();
                    tempTargetWord[k] = '*';
                    found = true;
                    break;
                }
            }

            // Not Found
            if (!found) {
                letterGrid[currentRow][j].setBackgroundColor(sf::Color(100, 100, 100));
                keyboard.changeLetterColor(letterGrid[currentRow][j].getCharacter(), sf::Color(100, 100, 100));
            }
        }
    }

    // Completely Correct
    bool isCorrect = true;
    for (int j = 0; j < 5; j++) {
        if (letterGrid[currentRow][j].getBackgroundColor() != sf::Color::Green) {
            isCorrect = false;
            break;
        }
    }

    if (isCorrect) {
        gameWon = true;
        updateStats();

        // Win Message
        messageText.setFont(font);
        messageText.setString("You WON!");
        messageText.setCharacterSize(32);
        messageText.setFillColor(sf::Color::Green);
        messageText.setPosition(280.f, 20.f);

        // Play again button
        PlayAgainButton();
    }
    else if (currentRow == 5) { 
        updateStats();
        // Lose Message
        messageText.setFont(font);
        messageText.setString("Better Luck Next Time!\nTarget Word: " + string(targetWord));
        messageText.setCharacterSize(24);
        messageText.setFillColor(sf::Color::Red);
        messageText.setPosition(280.f, 20.f);

        // Play again button
        PlayAgainButton();
    }

    // Move to next row
    currentRow++;
    currentColumn = 0;
}

void Wordle::PlayAgainButton() {
    gameWon = true; // Set game as over

    // Play again button
    playAgainButton.setSize(sf::Vector2f(150, 50));
    playAgainButton.setFillColor(sf::Color::Blue);
    playAgainButton.setPosition(280.f, 500.f);

    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(20);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setPosition(300.f, 510.f);
}

void Wordle::handleInput(sf::Event event, sf::RenderWindow* window)
{
    pauseResumeHandler.handleEvent(event, *window);
    if (pauseResumeHandler.isGamePaused()) {
        return;
    }

    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    if (showLeaderboard) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (leaderboard.isCloseButtonClicked(mousePos)) {
                showLeaderboard = false; // Close the leaderboard
                return;
            }
        }
    }

    if (gameWon && event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button != sf::Mouse::Left) return;

        // Handle back button and play again button clicks
        if (backButton.getGlobalBounds().contains(mousePos)) {
            shouldReturnToMenu = true;
            return;
        }
        if (playAgainButton.getGlobalBounds().contains(mousePos)) {
            resetGame();
            return;
        }
    }

    if (!showLeaderboard && event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Handle leaderboard button click
            if (leaderboardText.getGlobalBounds().contains(mousePos)) {
                showLeaderboard = true;
                return;
            }
        }
    }
    // Existing input handling if not returning to menu
    if (shouldReturnToMenu) return;

    // Handle keyboard input for letter entry
    if (event.type == sf::Event::TextEntered) {
        // Prevent input if game is won
        if (gameWon) return;

        // Check if the input is a letter
        if (isalpha(event.text.unicode)) {
            // Only allow input if we haven't filled the current row
            if (currentColumn < 5) {
                // Convert to uppercase
                char letter = toupper(static_cast<char>(event.text.unicode));
                letterGrid[currentRow][currentColumn].setCharacter(letter);
                currentColumn++;
            }
        }
    }
    // Handle backspace to delete letters
    else if (event.type == sf::Event::KeyPressed) {
        // Prevent input if game is won
        if (gameWon) return;

        if (event.key.code == sf::Keyboard::BackSpace) {
            // Remove last entered letter
            if (currentColumn > 0) {
                currentColumn--;
                letterGrid[currentRow][currentColumn].reset();
            }
        }
        // Handle Enter key to check word
        else if (event.key.code == sf::Keyboard::Enter) {
            checkWord();

            // Prevent going beyond the grid
            if (currentRow >= 6) {
                currentRow = 5;
            }
        }
    }
}

void Wordle::render(sf::RenderWindow& window) {
    windowPtr = &window;
    // Display the grid, guesses, and feedback to the screen
    window.draw(backgroundSprite);
    renderGrid(window);
    keyboard.render(window);
    window.draw(playerNameBorder);
    window.draw(playerNameText);
    window.draw(leaderboardText);
    renderLeaderboard(window);

    // Draw message if exists
    if (!messageText.getString().isEmpty()) {
        window.draw(messageText);
    }

    // Draw play again button if game is won
    if (gameWon) {
        window.draw(playAgainButton);
        window.draw(playAgainText);
    }

    // Draw back button
    window.draw(backButton);
    window.draw(backButtonText);
    pauseResumeHandler.draw(window);

}

void Wordle::setPlayer(Player* player)
{
    if (player == nullptr) {
        currentPlayer = new Player("Guest");
    }
    else {
        currentPlayer = player;
    }
    playerNameBorder.setSize({ 150, 50 });
    playerNameBorder.setPosition(650, 10);  // Top-right corner
    playerNameBorder.setFillColor(sf::Color::Cyan);

    playerNameText.setFont(font);
    playerNameText.setString(currentPlayer->getName());
    playerNameText.setCharacterSize(20);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(playerNameBorder.getPosition().x + 20, playerNameBorder.getPosition().y + 10);

    
}

void Wordle::renderGrid(sf::RenderWindow& window) {
    float boxSize = 40.f;
    float spacing = 10.f;
    sf::Vector2f startPosition(280.f, 70.f);

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            // Create and position the rectangle
            sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
            box.setFillColor(letterGrid[i][j].getBackgroundColor());
            box.setOutlineColor(sf::Color(0, 0, 0));    // Black outline
            box.setOutlineThickness(2.f);
            box.setPosition(
                startPosition.x + j * (boxSize + spacing),
                startPosition.y + i * (boxSize + spacing)
            );

            // Create and position the text
            sf::Text letter;
            letter.setFont(font);
            letter.setString(string(1, letterGrid[i][j].getCharacter()));
            letter.setCharacterSize(20);
            letter.setFillColor(sf::Color::Black);

            // Center the letter in the box
            sf::FloatRect letterBounds = letter.getLocalBounds();
            letter.setOrigin(letterBounds.left + letterBounds.width / 2.0f,
                letterBounds.top + letterBounds.height / 2.0f);
            letter.setPosition(
                box.getPosition().x + boxSize / 2.f,
                box.getPosition().y + boxSize / 2.f
            );

            // Draw the box and text
            window.draw(box);

            // Only draw the letter if it's not a space
            if (letterGrid[i][j].getCharacter() != ' ') {
                window.draw(letter);
            }
        }
    }
}

void Wordle::renderLeaderboard(sf::RenderWindow& window) {
    if (!showLeaderboard) return;
    leaderboard.display(window, "wordle", font);
}

void Wordle::updateStats() {
    // Check if we have a valid player
    if (!currentPlayer) return;

    // Update stats using the new Leaderboard class
    leaderboard.updatePlayerStats(
        currentPlayer->getName(),
        "wordle",
        gameWon,
        gameTimer.getElapsedTime().asSeconds()
    );
}
