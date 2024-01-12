#include <iostream>
#include <limits>
#include <vector>
#include "functions.hpp"

void setup(const std::string_view originalRandomWord, std::string& hiddenWord)
{
    // Introduction
    std::cout << "Welcome to C++man! (a variant of hangman)\n";
    std::cout << "To win: guess the word.\nTo lose: run out of pluses.\n";
    std::cout << "Note: Please only enter 1 character. Extra characters will be discarded.\n\n";

    // Number of underscores that the random word has will be assigned
    for (size_t i = 0; i < originalRandomWord.size(); ++i)
        hiddenWord.push_back('_');

#ifdef DEBUG
    std::cout << originalRandomWord << '\n';
#endif
}

void turn(const std::string_view originalRandomWord, std::string& hiddenWord, std::vector<char>& listOfGuesses, int& lives) 
{
    char guess{}; // Variable for the user's guess
   
    std::cout << "The word: " << hiddenWord << '\n';
    std::cout << "Lives: ";
    printLives(lives);
    std::cout << "You have guessed: ";
    printListOfGuesses(listOfGuesses);
    std::cout << "\nEnter your next letter: ";

    std::cin.get(guess);

    // Flushing the input buffer to make sure only 1 character is evaluated
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Early return if user guessed the same letter as before
    for (size_t i = 0; i < listOfGuesses.size(); ++i) {
        if (listOfGuesses.at(i) == guess) {
            std::cout << "You already guessed that. Try again.\n";
            return;
        }
    }

    // Since the guess is new, add it to the list
    listOfGuesses.emplace_back(guess);

    // Find the guess
    for (size_t i = 0; i < hiddenWord.size(); ++i) {
        if (guess == originalRandomWord.at(i)) {
            std::string tempGuess{};
            tempGuess += guess;
            hiddenWord.replace(i, 1, tempGuess);
        }
    }

    // Rechecking if the guess is correct, if not, remove a life (i have no better idea on how to do this shit fml)
    for (size_t i = 0; i < hiddenWord.size(); ++i)
        if (guess == originalRandomWord.at(i)) 
            return;
        
    --lives;
}

void printLives(const int lives)
{
    for (int i = 1; i <= lives; ++i)
        std::cout << '+';

    std::cout << '\n';
}

void printListOfGuesses(const std::vector<char>& listOfGuesses)
{
    for (size_t i = 0; i < listOfGuesses.size(); ++i)
        std::cout << listOfGuesses.at(i) << ' ';

    std::cout << '\n';
}

void winCheck(std::string_view hiddenWord) {
    size_t win = hiddenWord.find('_'); // find() returns -1 if nothing is found
    if (win == -1)                     // Therefore, if no underscores are found, all the letters have been found, leading to a win
    {
        std::cout << "You win!\n";
        std::exit(0);
    }
}