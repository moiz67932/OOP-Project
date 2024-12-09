#include "Hangman.h"

Hangman::Hangman() :pauseResumeHandler(sf::Vector2f(100.f, 50.f), font), gamePaused(false)
{
    std::cout << "Hangman Game Initialized!" << std::endl;
    loadFont();
    loadBackground();
    loadWrongEntrySprites();
    resetGame();
    currentPlayer = nullptr;



    playAgainButton.setSize(sf::Vector2f(200.f, 50.f));
    playAgainButton.setFillColor(sf::Color(165, 42, 42));
    playAgainButton.setPosition(350.f, 350.f);

    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(30);
    playAgainText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = playAgainText.getLocalBounds();
    playAgainText.setPosition(
        playAgainButton.getPosition().x + (playAgainButton.getSize().x - textBounds.width) / 2 - textBounds.left,
        playAgainButton.getPosition().y + (playAgainButton.getSize().y - textBounds.height) / 2 - textBounds.top
    );

    progressBarBackground.setSize(sf::Vector2f(200.f, 20.f)); // Set background size
    progressBarBackground.setFillColor(sf::Color(50, 50, 50)); // Grey background
    progressBarBackground.setPosition(550.f, 20.f); // Position it at the top

    progressBar.setSize(sf::Vector2f(200.f, 20.f)); // Initially full
    progressBar.setFillColor(sf::Color(0, 255, 0)); // Green color
    progressBar.setPosition(550.f, 20.f); // Same position as the background
    updateProgressBar();

    // Other initializations
    progressBarText.setFont(font); // Ensure font is loaded before this
    progressBarText.setCharacterSize(16);
    progressBarText.setFillColor(sf::Color::White);
    progressBarText.setPosition(420.f, 20.f); // Adjust position

    // Leaderboard Text
    leaderboardText.setFont(font);
    leaderboardText.setString("Leaderboard");
    leaderboardText.setCharacterSize(20);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setPosition(650, playerNameBorder.getPosition().y + 80);

}


Hangman::~Hangman() {
    std::cout << "Hangman Game Destroyed!" << std::endl;
}

void Hangman::loadFont() {
    if (!font.loadFromFile("./assets/fonts/font1.ttf")) {
        std::cout << "Font Loading Error!" << std::endl;
    }
}

void Hangman::loadBackground() {
    if (!backgroundTexture.loadFromFile("./assets/images/hangman.jpg")) {
        std::cout << "Background Loading Error!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Hangman::updateLivesText() {
    progressBarText.setString(std::to_string(totalLives) + "/6 Lives");
}

void Hangman::loadWrongEntrySprites() {
    hangmanFigure.loadTextures("./assets/images/wrongentry"); // Base path for textures
}

void Hangman::initializeGame() {
    guessedLettersCount = 0;
    std::fill(std::begin(guessedLetters), std::end(guessedLetters), '\0');

    // Set up the letter grid
    for (int i = 0; i < targetWord.size(); ++i) {
        letterGrid[0][i].setCharacter('_');
        letterGrid[0][i].setBackgroundColor(sf::Color::White);
        letterGrid[0][i].setTextColor(sf::Color::White);
    }
}

void Hangman::checkWordCompletion() {
    std::string guessedWord;

    // Build the guessed word from the grid
    for (int i = 0; i < targetWord.size(); ++i) {
        if (letterGrid[0][i].isLetterRevealed()) {
            guessedWord += letterGrid[0][i].getCharacter();
        }
        else {
            guessedWord += "_"; 
        }
    }

    // Compare the guessed word with the target word
    if (guessedWord == targetWord) {
        gameWon = true;
        gameOver = true; 
    }
}

void Hangman::checkLetter(char letter) {
    bool letterFound = false;

    // Check if the letter exists in the target word
    for (int i = 0; i < targetWord.size(); ++i) {
        if (targetWord[i] == letter) {
            letterGrid[0][i].setCharacter(letter);
            letterGrid[0][i].reveal();
            letterFound = true;
        }
    }

    // Update keyboard color and attempts based on whether the letter was correct
    if (letterFound) {
        keyboard.changeLetterColor(letter, sf::Color::Green);
    }
    else {
        keyboard.changeLetterColor(letter, sf::Color(100, 100, 100)); // Gray for incorrect guesses
        incorrectAttempts++;
        totalLives--;
        updateLivesText();
        updateProgressBar();
    }

    // Check for full word completion
    if (incorrectAttempts + guessedLettersCount > targetWord.size()-2) {
        checkWordCompletion();
    }

    // Check if game is over due to too many incorrect attempts
    if (incorrectAttempts >= 6) {
        gameOver = true;
    }
}

void Hangman::drawHangman(sf::RenderWindow& window) {
    hangmanFigure.draw(window, incorrectAttempts); // Use HangmanFigure to draw based on attempts
}

void Hangman::setPlayer(Player* player)
{
    if (player == nullptr) {
        currentPlayer = new Player("Guest");
    }
    else {
        currentPlayer = player;
    }
    playerNameBorder.setSize({ 100, 50 });
    playerNameBorder.setPosition(50, 10);  // Top-right corner
    playerNameBorder.setFillColor(sf::Color(0, 255, 255, 128));
    playerNameBorder.setOutlineColor(sf::Color::White);
    playerNameBorder.setOutlineThickness(2.0);

    playerNameText.setFont(font);
    playerNameText.setString(currentPlayer->getName());
    playerNameText.setCharacterSize(20);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(playerNameBorder.getPosition().x + 24, playerNameBorder.getPosition().y + 10);


}


void Hangman::renderGrid(sf::RenderWindow& window) {
    for (int i = 0; i < targetWord.size(); ++i) {
        sf::Text letterText;
        letterText.setFont(font);

        // Display the character if revealed, otherwise show an underscore
        if (letterGrid[0][i].isLetterRevealed()) {
            letterText.setString(std::string(1, letterGrid[0][i].getCharacter()));
        }
        else {
            letterText.setString("_");
        }
        letterText.setCharacterSize(50);
        letterText.setFillColor(letterGrid[0][i].getTextColor());
        letterText.setPosition(400.f + i * 60.f, 200.f);  // Adjust positions as needed
        window.draw(letterText);
    }
}


void Hangman::handleInput(sf::Event event, sf::RenderWindow& window) {
    pauseResumeHandler.handleEvent(event, window);

    if (pauseResumeHandler.isGamePaused()) {
        return; 
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (playAgainButton.getGlobalBounds().contains(mousePos)) {
            resetGame(); 
            return; 
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button != sf::Mouse::Left) return;

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (leaderboardText.getGlobalBounds().contains(mousePos)) {
            showLeaderboard = true;
        }

        // Handle close button inside leaderboard
        if (showLeaderboard) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (leaderboard.isCloseButtonClicked(mousePos)) {
                    showLeaderboard = false; // Close the leaderboard
                    return;
                }
            }
        }
    }

    if (showLeaderboard) {
        return; 
    }

    if (!gameOver && event.type == sf::Event::TextEntered) {
        if (std::isalpha(event.text.unicode)) {
            char guessedLetter = std::toupper(event.text.unicode);
            bool alreadyGuessed = false;

            // Check if the letter is already in the array
            for (int i = 0; i < guessedLettersCount; ++i) {
                if (guessedLetters[i] == guessedLetter) {
                    alreadyGuessed = true;
                    break;
                }
            }

            if (!alreadyGuessed && guessedLettersCount < 26) {
                guessedLetters[guessedLettersCount] = guessedLetter; 
                guessedLettersCount++;
                checkLetter(guessedLetter);

                if (gameWon) {
                    gameOver = true;
                    updateStats();

                }
            }
        }
    }

    if (shouldReturnToMenu) return;
}


void Hangman::startGame() {
    std::cout << "Starting Hangman Game!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman"); // Create a window for the selection
    selectedCategoryIndex = -1;
    while (selectedCategoryIndex == -1) {
        window.clear();
        displayCategories(window);
        window.display();
    }

    resetGame();
}

void Hangman::endGame() {
    if (gameWon) {
        std::cout << "You WON!" << std::endl;
    }
    else {
        std::cout << "You LOST the game! The word was: " << targetWord << std::endl;
    }
    resetGame();
}


void Hangman::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    renderGrid(window);
    drawHangman(window);

    window.draw(progressBarBackground); // Draw the background
    window.draw(progressBar);
    window.draw(progressBarText);

    if (gameOver) {
        messageText.setFont(font);
        messageText.setString(gameWon ? "You WON!" : "Game Over! The word was: " + targetWord);
        messageText.setCharacterSize(24);
        messageText.setFillColor(sf::Color::White);
        messageText.setPosition(350.f, 300.f);
        window.draw(messageText);

        window.draw(playAgainButton);
        window.draw(playAgainText);
    }
    keyboard.render(window);
    pauseResumeHandler.draw(window);

    window.draw(playerNameBorder);
    window.draw(playerNameText);
    window.draw(leaderboardText);
    renderLeaderboard(window);

}



void Hangman::resetGame() {
    keyboard.resetKeyboard();
    //shouldReturnToMenu = false;
    gameWon = false;
    gameOver = false;  // Ensure gameOver is set to false
    incorrectAttempts = 0;
    totalLives = 6;
    guessedLettersCount = 0;
    selectCategory(selectedCategoryIndex);
    initializeGame();  // Reset game state

    updateProgressBar();
    updateLivesText();



    //std::cout << "Game reset: Lives = " << totalLives << ", Word = " << targetWord << std::endl;
}


void Hangman::updateProgressBar() {
    float progress = static_cast<float>(totalLives) / 6; // Calculate remaining lives as a percentage
    progressBar.setSize(sf::Vector2f(200.f * progress, 20.f)); // Adjust the width based on progress

    // Change color based on lives remaining
    if (progress > 0.5f) {
        progressBar.setFillColor(sf::Color(0, 255, 0)); // Green for >50% lives
    }
    else if (progress > 0.25f) {
        progressBar.setFillColor(sf::Color(255, 165, 0)); // Orange for 25-50% lives
    }
    else {
        progressBar.setFillColor(sf::Color(255, 0, 0)); // Red for <25% lives
    }
}

void Hangman::displayCategories(sf::RenderWindow& window) {

    const std::string* categoryNames = category.getCategoryNames();
    sf::Text categoryText;

    categoryText.setFont(font);
    categoryText.setCharacterSize(24);
    categoryText.setFillColor(sf::Color::White);

    for (int i = 0; i < 5; ++i) {
        categoryText.setString(categoryNames[i]);
        categoryText.setPosition(300.f, 100.f + i * 50.f); // Position each category option

        sf::FloatRect bounds = categoryText.getGlobalBounds();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                selectCategory(i);
            }
        }

        window.draw(categoryText);
    }
}

// Member function implementation
std::string Hangman::getRandomWordFromCategory(int categoryIndex) {
    // Get the category name from the index
    const std::string* categoryNames = category.getCategoryNames();
    std::string categoryName = categoryNames[categoryIndex];

    // Fetch a random word from the chosen category
    return category.getRandomWord(categoryIndex);
}

void Hangman::selectCategory(int categoryIndex) {
    selectedCategoryIndex = categoryIndex;
    const std::string* categoryNames = category.getCategoryNames();
    selectedCategory = categoryNames[categoryIndex];

    // Select a new random word using the new member function
    targetWord = getRandomWordFromCategory(categoryIndex);
    std::transform(targetWord.begin(), targetWord.end(), targetWord.begin(), ::toupper);

    initializeGame(); // Proceed with the game
}


void Hangman::renderLeaderboard(sf::RenderWindow& window) {
    if (!showLeaderboard) return;
    leaderboard.display(window, "hangman", font);
}

void Hangman::updateStats() {
    // Check if we have a valid player
    if (!currentPlayer) return;

    // Update stats using the new Leaderboard class
    leaderboard.updatePlayerStats(
        currentPlayer->getName(),
        "hangman",
        gameWon,
        gameTimer.getElapsedTime().asSeconds()
    );
}

