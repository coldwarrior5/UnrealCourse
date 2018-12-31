#include "pch.h"
#include "FBullCowGame.h"
#include <iostream>
#include <string>

// To make Unreal friendly
using FText = std::string;
using int32 = int;

// Function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintResult(FBullCowCount Count);
bool AskToPlayAgain();
void PrintGameSummary();

// Instantiate a new game
FBullCowGame BCGame;

int main()
{
	// Loop until the user says otherwise
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	// Exit the application
	return 0;
}

// A bit of ASCII art for users to enjoy
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "         __n__n__" << std::endl;
	std::cout << "  .------`-\\00/-'" << std::endl;
	std::cout << "  / ##  ## (oo)" << std::endl;
	std::cout << " / \\## __   ./" << std::endl;
	std::cout << "    |//YY \\|/" << std::endl;
	std::cout << "    |||   |||" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		PrintResult(BullCowCount);
	}
	PrintGameSummary();
}

// Loop continuously until user gives a valid guess
FText GetValidGuess()
{
	FText Guess;
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		const int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter an all lowercase letter word." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		default:
			// We assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until we get a valid guess
	return Guess;
}

// Repeat the guess back to the player
void PrintResult(FBullCowCount Count)
{
	std::cout << "Bulls: " << Count.Bulls  << ", Cows: " << Count.Cows << std::endl;
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "\n\n\nDo you wish to play again (y/n)?" << std::endl;
	getline(std::cin, Response);
	if(Response[0] == 'y' || Response[0] == 'Y')
	{
		BCGame.Reset();
		return true;
	}
	return false;
}

void PrintGameSummary()
{
	if(BCGame.IsGameWon())
	{
		std::cout << std::endl << "Well done, you won.";
	}
	else
	{
		std::cout << std:: endl << "You lost, better luck next time.";
	}
}
