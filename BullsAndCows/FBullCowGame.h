#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EWordStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// This is contract
class FBullCowGame
{
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString Guess) const;

	void Reset();
	FBullCowCount SubmitGuess(FString Guess);


private:
	int32 CurrentTry{};
	int32 MaxTries{};
	FString MyHiddenWord;
	bool IsAnIsogram(FString Guess) const;
	bool IsLowercase(FString Guess) const;
	bool IsSameLength(FString Guess) const;
};
