#include "pch.h"
#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const {	return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const
{
	return false;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plant";
	constexpr int32 MAX_TRIES = 8;

	MaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	CurrentTry = 1;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsAnIsogram(Guess))
		return EGuessStatus::Not_Isogram;
	else if (!IsLowercase(Guess))
		return  EGuessStatus::Not_Lowercase;
	else if (!IsSameLength(Guess))
		return EGuessStatus::Wrong_Length;
	else
		return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;
	const int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if(Guess[i] == MyHiddenWord[j])
			{
				if (i == j)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}

	return BullCowCount;
}

bool FBullCowGame::IsAnIsogram(FString Guess) const
{
	for (int i = 0; i < Guess.length(); i++)
	{
		for (int j = i + 1; j < Guess.length(); j++)
		{
			if (Guess[i] == Guess[j])
				return false;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (int i = 0; i < Guess.length(); i++)
	{
		if (isupper(Guess[i]))
			return false;
	}
	return true;
}

bool FBullCowGame::IsSameLength(FString Guess) const
{
	return Guess.length() == MyHiddenWord.length();
}
