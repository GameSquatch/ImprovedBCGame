//
//  FBullCowGame.hpp
//  Bulls and Cows2
//
//  Created by Ezekiel Williams on 12/18/16.
//  Copyright © 2016 Ezekiel Williams. All rights reserved.
//

#ifndef FBullCowGame_h
#define FBullCowGame_h

#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Wrong_Length,
    Not_Lowercase,
    Not_Isogram
};

class FBullCowGame
{
public:
    FBullCowGame(); // constructor
    
    void Reset();// TODO make a more rich return value
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    
    EGuessStatus CheckGuessValidity(FString) const;
    
    FBullCowCount SubmitValidGuess(FString);
    
    
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
    
};


#endif /* FBullCowGame_h */
