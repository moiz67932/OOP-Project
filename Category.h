#pragma once
#include <string>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator

class Category {
private:
    static const int CATEGORY_COUNT = 5;
    static const int WORDS_PER_CATEGORY = 5;

    std::string categoryNames[CATEGORY_COUNT] = { "Food", "Places", "Sports", "Things", "Animals" };
    std::string food[WORDS_PER_CATEGORY] = { "Pizza", "Burger", "Sushi", "Pasta", "Salad" };
    std::string places[WORDS_PER_CATEGORY] = { "Paris", "Tokyo", "London", "Dubai", "Sydney" };
    std::string sports[WORDS_PER_CATEGORY] = { "Cricket", "Soccer", "Tennis", "Hockey", "Rugby" };
    std::string things[WORDS_PER_CATEGORY] = { "Laptop", "Bottle", "Pencil", "Chair", "Table" };
    std::string animals[WORDS_PER_CATEGORY] = { "Tiger", "Elephant", "Penguin", "Rabbit", "Dolphin" };

    // Function to get the word array for a given category index
    const std::string* getCategoryWords(int index) const;

public:
    Category();

    // Display available categories
    const std::string* getCategoryNames() const;

    // Get a random word from a chosen category index
    std::string getRandomWord(int categoryIndex);
};
