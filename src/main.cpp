#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include "functions.hpp"
#include "macros.hpp"
#include "random.h"

// Ideas:
// Add different languages
// Add different difficulties (harder difficulties = longer words + less lives)
// Add more words

namespace WordList
{
    // Add as many words as you want! The function in this namespace allows it automatically
    const std::vector<std::string_view> words { "absurd", "lucky", "subway", "pandemonium", "flawless", "jazz", "mystify", "electric", "backpack", "zephyr", "ember", "cinder", "megabyte", "mystery", "broccoli" , "account", "balls", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size()-1)];
    }
}

#ifdef DEBUG
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}

void operator delete(void* ptr, size_t size)
{
    std::cout << "Freeing " << size << " bytes\n";
    free(ptr);
}
#endif

int main() 
{
    std::string_view originalRandomWord = WordList::getRandomWord(); // Get a random word from the list
    std::string hiddenWord{}; // Word that will be modified during the game
    setup(originalRandomWord, hiddenWord);

    std::vector<char> listOfGuesses{}; // List of guesses storing the user's already used characters so they don't repeat
    constexpr std::array<char, 5> vowels { 'a', 'e', 'i', 'o', 'u' };
    int lives = 7;
    while (lives != 0) {
        turn(originalRandomWord, hiddenWord, listOfGuesses, lives);

        winCheck(hiddenWord);
    }
    std::cout << "You lose.\n";
}