#pragma once
#include <cstring>
#include <cstdlib>
#include <ctime>

class WordDictionary {
private:
    static const int MAX_WORDS = 50;
    static const int WORD_LENGTH = 6;
    char dictionary[MAX_WORDS][WORD_LENGTH];

public:
    // Constructor to initialize the dictionary
    WordDictionary();

    // Get a random word from the dictionary
    void getRandomWord(char* word);

    // Get total number of words in the dictionary
    int getTotalWords() const;

    // Optional: Add methods to add or remove words from the dictionary
    void addWord(const char* word);
    void removeWord(const char* word);

    // Optional: Check if a word exists in the dictionary
    bool wordExists(const char* word) const;
};