#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
void print_intro();
string get_guess();
void print_guess(string Guess);

constexpr int WORD_LENGTH = 5;
constexpr int NUMBER_OF_TURNS = 5;

int main()
{
	print_intro();
	for (int i = 0; i < NUMBER_OF_TURNS; i++)
	{
		string Guess = get_guess();
		print_guess(Guess);
	}
	return 0;
}

// Introduce the game
void print_intro()
{
	cout << "Welcome to Bulls and Cows, a fun word game." << endl;
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?" << endl;
}

// Get a guess from a player
string get_guess()
{
	cout << endl << "Enter your guess: ";
	string Guess;
	getline(cin, Guess);
	return Guess;
}

// Repeat the guess back to the player
void print_guess(string Guess)
{
	cout << "Your guess was: " << Guess << endl;
}