#pragma once
#include <string_view>
#include <vector>

// Runs at startup to setup the "hiddenWord" variable and welcome the user
void setup(const std::string_view originalRandomWord, std::string& hiddenWord);

// Runs on every turn
void turn(const std::string_view originalRandomWord, std::string& hiddenWord, std::vector<char>& listOfGuesses, int& lives);

// Prints how many lives the user has
void printLives(const int lives);

// Prints the user's guesses
void printListOfGuesses(const std::vector<char>& listOfGuesses);

// Checks if the player guessed the word correctly, therefore winning
void winCheck(std::string_view hiddenWord);