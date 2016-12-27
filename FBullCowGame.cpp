//
//  FBullCowGame.cpp
//  Bulls and Cows2
//
//  Created by Ezekiel Williams on 12/18/16.
//  Copyright © 1998-2016 Epic Games. All rights reserved.
//
#include <stdio.h>
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}


FBullCowGame::FBullCowGame()
{
    Reset();
}


void FBullCowGame::Reset()// TODO make a more rich return value
{
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    
    return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const // TODO make a more rich return value
{
    if (!IsIsogram(Guess)) // check if isogram using helper function returning a bool
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (Guess.length() != MyHiddenWord.length()) // check length
    {
        return EGuessStatus::Wrong_Length;
    }
    else if (!IsLowercase(Guess)) // check capital letters
    {
        return EGuessStatus::Not_Lowercase;
    }
    else
    {
        return EGuessStatus::OK;
    }
}


bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        
        if (LetterSeen[Letter])
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }
    
    
    return true;
}


bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++; // increment try number when guess is valid
    
    
    FBullCowCount BullCowCount; // object to return int32 Bulls and int32 Cows count
    
    
    int32 WordLength = MyHiddenWord.length();
    
    for (int32 i = 0; i < WordLength; i++)
    {
        for (int32 j = 0; j < WordLength; j++)
        {
            if (MyHiddenWord[i] == Guess[j]) // if hidden word letter is equal to guess word letter
            {
                if (i == j)                  // if they are in the same position (bull)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;    // else, they must be a cow
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    
    return BullCowCount;
    
}




