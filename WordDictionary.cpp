#include "WordDictionary.h"

WordDictionary::WordDictionary() {
    // Initialize 50 words
    strcpy_s(dictionary[0], "APPLE");
    strcpy_s(dictionary[1], "BEACH");
    strcpy_s(dictionary[2], "CHAIR");
    strcpy_s(dictionary[3], "DANCE");
    strcpy_s(dictionary[4], "EAGLE");
    strcpy_s(dictionary[5], "FENCE");
    strcpy_s(dictionary[6], "GRAPE");
    strcpy_s(dictionary[7], "HOUSE");
    strcpy_s(dictionary[8], "INDIA");
    strcpy_s(dictionary[9], "JUICE");
    strcpy_s(dictionary[10], "KNIFE");
    strcpy_s(dictionary[11], "LEMON");
    strcpy_s(dictionary[12], "MOUSE");
    strcpy_s(dictionary[13], "NIGHT");
    strcpy_s(dictionary[14], "OCEAN");
    strcpy_s(dictionary[15], "PIANO");
    strcpy_s(dictionary[16], "QUEEN");
    strcpy_s(dictionary[17], "RIVER");
    strcpy_s(dictionary[18], "SNAKE");
    strcpy_s(dictionary[19], "TIGER");
    strcpy_s(dictionary[20], "WATER");
    strcpy_s(dictionary[21], "BRAIN");
    strcpy_s(dictionary[22], "CLOUD");
    strcpy_s(dictionary[23], "DREAM");
    strcpy_s(dictionary[24], "EARTH");
    strcpy_s(dictionary[25], "FLAME");
    strcpy_s(dictionary[26], "GRACE");
    strcpy_s(dictionary[27], "HEART");
    strcpy_s(dictionary[28], "IVORY");
    strcpy_s(dictionary[29], "JOKER");
    strcpy_s(dictionary[30], "KOALA");
    strcpy_s(dictionary[31], "LION");
    strcpy_s(dictionary[32], "MOON");
    strcpy_s(dictionary[33], "NOBLE");
    strcpy_s(dictionary[34], "OPERA");
    strcpy_s(dictionary[35], "PEARL");
    strcpy_s(dictionary[36], "QUEST");
    strcpy_s(dictionary[37], "RAVEN");
    strcpy_s(dictionary[38], "STORM");
    strcpy_s(dictionary[39], "TRUST");
    strcpy_s(dictionary[40], "SMILE");
    strcpy_s(dictionary[41], "WORLD");
    strcpy_s(dictionary[42], "LIGHT");
    strcpy_s(dictionary[43], "SMART");
    strcpy_s(dictionary[44], "HAPPY");
    strcpy_s(dictionary[45], "PEACE");
    strcpy_s(dictionary[46], "FIGHT");
    strcpy_s(dictionary[47], "POWER");
    strcpy_s(dictionary[48], "SPEED");
    strcpy_s(dictionary[49], "MAGIC");
}

void WordDictionary::getRandomWord(std::string& targetWord) {
    //// Seed the random number generator

    //// Select a random word from the dictionary
    //int randomIndex = rand() % MAX_WORDS;
    //strcpy_s(word, WORD_LENGTH, dictionary[randomIndex]);
    static bool seeded = false;
    
    srand(time(nullptr));

    int randomIndex = std::rand() % 50;
    targetWord = dictionary[randomIndex];
}

int WordDictionary::getTotalWords() const {
    return MAX_WORDS;
}

void WordDictionary::addWord(const char* word) {
    // Check if we have space to add a word
    if (getTotalWords() < MAX_WORDS) {
        // Note: In a real implementation, you'd want to add proper bounds checking
        strcpy_s(dictionary[getTotalWords()], WORD_LENGTH, word);
    }
}

void WordDictionary::removeWord(const char* word) {
    // Note: This is a simplified implementation
    for (int i = 0; i < MAX_WORDS; ++i) {
        if (strcmp(dictionary[i], word) == 0) {
            // Shift remaining words to fill the gap
            for (int j = i; j < MAX_WORDS - 1; ++j) {
                strcpy_s(dictionary[j], WORD_LENGTH, dictionary[j + 1]);
            }
            break;
        }
    }
}

bool WordDictionary::wordExists(const char* word) const {
    for (int i = 0; i < MAX_WORDS; ++i) {
        if (strcmp(dictionary[i], word) == 0) {
            return true;
        }
    }
    return false;
}