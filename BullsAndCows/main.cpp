#include "pch.h"
#include "FBullCowGame.h"
#include <iostream>
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
void PrintGuess(FText Guess);
bool AskToPlayAgain();

// Instantiate a new game
FBullCowGame BCGame;

constexpr int32 WORD_LENGTH = 5;


int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	// Exit the application
	return 0;
}

void PrintIntro()
{
	// TODO get the word length form the class
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	// TODO change from FOR to WHILE loop once we are validating tries
	for (int32 i = 0; i < MaxTries; i++)
	{
		FText Guess = GetGuess();
		// UNDONE make loop checking valid
		// UNDONE submit valid guess to the game
		 PrintGuess(Guess);
		
	}
	// TODO add a game summary

}

// Get a guess from a player
FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << std::endl << "Try " << CurrentTry << ". Enter your guess: ";
	FText Guess;
	getline(std::cin, Guess);
	return Guess;
}

// Repeat the guess back to the player
void PrintGuess(FText Guess)
{
	std::cout << "Your guess was: " << Guess << std::endl;
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "Do you wish to play again (y/n)?" << std::endl;
	getline(std::cin, Response);
	return Response[0] == 'y' || Response[0] == 'Y';
}
