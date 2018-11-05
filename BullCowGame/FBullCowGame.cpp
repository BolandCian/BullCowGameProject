#include "FBullCowGame.h"
#include <map>
#define TMap std::map
#pragma once

using int32 = int;

FBullCowGame::FBullCowGame() //constructor
{
	Reset();
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "hackers";
	MyHiddenWord = HIDDEN_WORD;
	constexpr int32 CURRENT_TRIES = 1;
	MyCurrentTry = CURRENT_TRIES;
	bGameIsWon = false;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!bIsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}

	else if (!bIsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess is wrong length
	{
		return EGuessStatus::Wrong_Length;

	}
		// return error
	else // otherwise 
	{
		return EGuessStatus::OK;
	}
		
		// return OK
}

// receives a Valid guess, increments turn, and returns count ^^
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the gidden word
		
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			// compare letters against the guess
			for (int32 GChar = 0; GChar < WordLength; GChar++) {
				//if they match then
				if (Guess[GChar] == MyHiddenWord[MHWChar]) {
					if (MHWChar == GChar) {
						//if they're in the same place
						BullCowCount.Bulls++; //increment bulls 
					}	
					else {
						BullCowCount.Cows++;//Must be a cows
					}
						
				}
			}
		}

		if (BullCowCount.Bulls == WordLength) {
			bGameIsWon = true;
		}
		else
		{
			bGameIsWon = false;
		}
	return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	
	TMap<char, bool> LetterSeen; //  setup our map
	for (auto Letter : Word)		// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) 	// if the letter is in the map
			{ return false; }	// we do NOT have an isogram
		else {
			LetterSeen[Letter] = true; // otherwise
			// add the letter to the map as seen
		}
				
			
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::bIsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		 }
		
	}
	return true;
}

