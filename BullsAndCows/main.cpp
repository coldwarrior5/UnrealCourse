#include "pch.h"
#include "FBullCowGame.h"
#include <iostream>
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
void PrintResult(FBullCowCount Count);
bool AskToPlayAgain();

// Instantiate a new game
FBullCowGame BCGame;

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
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
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
		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		PrintResult(BullCowCount);
		
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
void PrintResult(FBullCowCount Count)
{
	std::cout << "Bulls: " << Count.Bulls << std::endl << "Cows: " << Count.Cows << std::endl;
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "Do you wish to play again (y/n)?" << std::endl;
	getline(std::cin, Response);
	return Response[0] == 'y' || Response[0] == 'Y';
}
