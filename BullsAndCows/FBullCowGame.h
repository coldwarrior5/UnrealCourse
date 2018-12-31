/* The game logic (no view code or direct user interaction)
 * The game is a simple guess the word game .
 */
#pragma once
#include <string>
#include <vector>
#include <map>
#define TArray std::vector
#define TMap std::map

// To make Unreal friendly
using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// This is contract
class FBullCowGame
{
public:
	FBullCowGame() : IsogramDictionary({ "planet", "cake", "mother", "wheat", "bothering", "brawl", "brain", "left", "lean", "medium", "isogram", "panther", "plot", "rim", "mare", "nightmare", "fly", "twist", "twister", "crow", "cry", "duo", "pant", "overwhelm", "spire" }),
		WordLengthMaxTries({ {2,3}, {3,4}, {4,6}, {5,10}, {6,16}, {7,24}, {8,24}, {9,36}, {10, 50} })
	{
		Reset();
	}; // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);


private:
	int32 CurrentTry{};
	FString MyHiddenWord;
	bool bGameIsWon{};
	TArray<std::string> IsogramDictionary;
	TMap<int32, int32> WordLengthMaxTries;

	bool IsAnIsogram(FString) const;
	bool IsAnIsogramSlower(FString) const;
	bool IsLowercase(FString) const;
	bool IsSameLength(FString) const;

	FString PickNextWord() const;
};
