#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
class SoundSystem; // Forward declaration
#include "Snake.h"     
#include "Wordle.h"    
#include "Hangman.h"   
#include <iostream>



class Screen {
public:
    Screen(int resolutionX, int resolutionY);
    ~Screen();
    void manageState(Menu* menu, Snake* snake, Wordle* wordle, Hangman* hangman);
    void renderCurrentState(sf::RenderWindow& window);
    void setSoundSystem(SoundSystem* currentsoundSystem);

private:
    sf::RenderWindow* window;  
    Game* gameState;        
    Menu* menuState;
    SoundSystem* soundSystem;

};