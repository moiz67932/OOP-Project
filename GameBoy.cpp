//void GameBoy::initVariables()
//{
//	this->window = nullptr;
//
//	this->points=0;
//	this->health = 10;
//	this->enemySpawnTimerMax=10.f;
//	this->enemySpawnTimer=this->enemySpawnTimerMax;
//	this->maxEnemies=5;
//	this->endGame = false;
//
//	// Music Path
//	this->menuMusicPath = "./assets/music/music.mp3";
//
//	// Screen
//	this->screen = new Screen(this->window);
//}
//
//void GameBoy::initWindow()
//{
//	this->videoMode.height=700;
//	this->videoMode.width=1000;
//	this->window = new sf::RenderWindow(this->videoMode, "SFML Game", sf::Style::Default);
//	this->window->setFramerateLimit(60);
//}
//
//void GameBoy::initEnemy()
//{
//	this->enemy.setPosition(sf::Vector2f(100.f, 100.f));
//	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
//	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
//	this->enemy.setFillColor(sf::Color::Cyan);
//	this->enemy.setOutlineColor(sf::Color::Black);
//	this->enemy.setOutlineThickness(1.5f);
//}
//
//void GameBoy::initFont()
//{
//	if (!this->font.loadFromFile("./assets/fonts/TabernaSerif-Regular.ttf"))
//		std::cout << "FONT LOADING ERROR";
//}
//
//void GameBoy::initText()
//{
//	this->uiText.setFont(this->font);
//	this->uiText.setCharacterSize(24);
//	this->uiText.setFillColor(sf::Color::White);
//	this->uiText.setString("HALO!!");
//}
//
//void GameBoy::initMusic()
//{
//	this->soundSystem.initMusic(this->menuMusicPath);
//	this->soundSystem.playMusic();
//}
//
//void GameBoy::updateMousePos()
//{
//	this->mousePosition = sf::Mouse::getPosition(*this->window);
//	this->mousePositionView = this->window->mapPixelToCoords(this->mousePosition);
//}
//
//GameBoy::GameBoy()
//{
//	this->initVariables();
//	this->initFont();
//	this->initText();
//	this->initWindow();
//	this->initEnemy();
//	this->initMusic();
//}
//
//GameBoy::~GameBoy()
//{
//	delete this->screen;
//	delete this->window;
//}
//
//const bool GameBoy::running() const
//{
//	return this->window->isOpen();
//}
//
//bool GameBoy::getEndGame()
//{
//	return this->endGame;
//}

//void GameBoy::pollEvents()
//{
//	while (this->window->pollEvent(this->ev))
//	{
//		// Close window: exit
//		if (this->ev.type == sf::Event::Closed)
//			this->window->close();
//	}
//}

//void GameBoy::updateText()
//{
//	std::stringstream ss;
//	ss << "Points: " << this->points << std::endl
//		<< "Health: " << this->health << std::endl;
//
//	this->uiText.setString(ss.str());
//}

//void GameBoy::renderText(sf::RenderTarget& target)
//{
//	target.draw(this->uiText);
//}
//
//void GameBoy::update()
//{
//	this->pollEvents();
//
//	if (!this->endGame) {	
//	this->updateMousePos();
//	this->updateText();
//	this->updateEnemy();
//	}
//
//	// Game Ending Logic
//	if (this->health <= 0)
//		this->endGame = true;
//
//}
//
//void GameBoy::render()
//{
//	this->window->clear();
//	//this->renderEnemy(*this->screen.getWindow());
//	//this->renderText(*this->screen.getWindow());
//	//this->renderEnemy(*this->window);
//	//this->renderText(*this->window);
//	this->screen->renderMenu();
//	this->window->display();
//}
//


#include "GameBoy.h"

GameBoy::GameBoy() {
    // Initialize Screen and Menu
    screen = new Screen(800, 600);
    soundSystem = new SoundSystem();
    soundSystem->setScreen(screen);
}

GameBoy::~GameBoy() {
    // Clean up dynamically allocated memory
    delete screen;
    delete soundSystem;
}

void GameBoy::start() {
    // Use the screen to display the menu
    screen->setSoundSystem(soundSystem);
    screen->manageState(&menu, &snakeGame, &wordleGame, &hangmanGame);

}
