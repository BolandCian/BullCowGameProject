#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};



enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase



};



class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); // TODO make a more rich return value.
	 
	
									  
	// counts bulls and cows and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);




private:
	// See Constructor for initlisation
	int32 MyCurrentTry ;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool bIsIsogram(FString) const ;
	bool bIsLowercase(FString) const;
};
