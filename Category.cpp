#include "Category.h"

Category::Category() {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

const std::string* Category::getCategoryNames() const {
    return categoryNames;
}

const std::string* Category::getCategoryWords(int index) const {
    switch (index) {
    case 0: return food;
    case 1: return places;
    case 2: return sports;
    case 3: return things;
    case 4: return animals;
    default: return nullptr;
    }
}

std::string Category::getRandomWord(int categoryIndex) {
    const std::string* words = getCategoryWords(categoryIndex);
    if (words) {
        int randomIndex = std::rand() % WORDS_PER_CATEGORY; // Select a random index
        return words[randomIndex];
    }
    return ""; // Return an empty string if the index is invalid
}
