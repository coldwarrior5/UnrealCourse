#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// This is contract
class FBullCowGame
{
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset();
	bool CheckGuessValidity(FString);


private:
	int32 CurrentTry;
	int32 MaxTries;
};
