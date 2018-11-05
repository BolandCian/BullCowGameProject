/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame.

*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"
#pragma once


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

	//Entry Point for application
int main()
{

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0; //exit of application

}


void PrintIntro() 
{	
	// introduce the game
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "\n\n Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "In this game, the number of bulls is an indication of how many letters are right and in the correct spot,\n ";
	std::cout << "If you get a cow it means you have a correct letter but it is in the wrong spot.\nTry moving it around.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();


	// Loop for the number of turns asking for guesses
	//Is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) {
		FText Guess = GetValidGuess(); 
	

		//Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << std::endl;

		std::cout << "Your guess was : " << Guess << "\n\n";
		
	}

	PrintGameSummary();
	//TODO add a game summary.
	return;

}


FText GetValidGuess()  //loop continuially until user gets valid guess
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << MyCurrentTry <<  " of " << BCGame.GetMaxTries() << " Enter your guess : ";
		
		std::getline(std::cin, Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "\nPlease enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please ensure all letters are lowercase.\n\n";
			break;
		default:
			
			break;

		}
	} while (Status != EGuessStatus::OK); // keep looping till we get no errors
	return Guess;
}
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) : ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time \n";
	}
}