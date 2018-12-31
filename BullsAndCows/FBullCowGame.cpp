#include "pch.h"
#include "FBullCowGame.h"
#include <map>
#include <vector>
#include <ctime>
// ReSharper disable once CppInconsistentNaming
#define TMap std::map
#define TArray std::vector

// To make Unreal friendly
using int32 = int;

int32 FBullCowGame::GetCurrentTry() const {	return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	return WordLengthMaxTries.at(GetHiddenWordLength());
}


void FBullCowGame::Reset()
{
	MyHiddenWord = PickNextWord();
	CurrentTry = 1;
	bGameIsWon = false;
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

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;
	const int32 WordLength = MyHiddenWord.length(); // Assuming same length as guess
	for (int32 GuessIter = 0; GuessIter < WordLength; GuessIter++)
	{
		for (int32 HiddenWIter = 0; HiddenWIter < WordLength; HiddenWIter++)
		{
			if(Guess[GuessIter] == MyHiddenWord[HiddenWIter])
			{
				if (GuessIter == HiddenWIter)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
		bGameIsWon = true;

	return BullCowCount;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool FBullCowGame::IsAnIsogramSlower(FString Word) const
{
	for (int32 i = 0; i < int32(Word.length()); i++)
	{
		for (int32 j = i + 1; j < int32(Word.length()); j++)
		{
			if (Word[i] == Word[j])
				return false;
		}
	}
	return true;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool FBullCowGame::IsAnIsogram(FString Word) const
{
	if (Word.length() <= 1)
		return true;

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)	// For all letters of the word
	{
		Letter = tolower(Letter);	// Handle mixed case
		if (LetterSeen[Letter])
			return false;
		LetterSeen[Letter] = true;
	}
	return true;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto C : Word)
	{
		if (isupper(C))
			return false;
	}
	return true;
}

bool FBullCowGame::IsSameLength(FString Guess) const
{
	return int32(Guess.length()) == GetHiddenWordLength();
}

FString FBullCowGame::PickNextWord() const
{
	srand(time(nullptr));
	const int RandomChoice = rand() % IsogramDictionary.size();
	return IsogramDictionary.at(RandomChoice);
}
