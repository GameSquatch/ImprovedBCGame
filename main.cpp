//
//  main.cpp
//  Bulls and Cows2
//
//  Created by Ezekiel Williams on 12/18/16.
//  Copyright © 2016 Ezekiel Williams. All rights reserved.
//

#include <iostream>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();



FBullCowGame BCGame;


int main(int32 argc, const char * argv[]) {
    
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    
    std::cout << std::endl;
    return 0;
}


void PrintIntro()
{
    
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n\n\n";
    std::cout << "        BULLS            AND               COWS           \n" << std::endl;
    std::cout << "           \\     /                                       " << std::endl;
    std::cout << "   ________------                   ------________        " << std::endl;
    std::cout << "  /|       |o  o|                   |o  o|       |\\      " << std::endl;
    std::cout << " / |_______\\    /                   \\    /_______| \\   " << std::endl;
    std::cout << "   | '    | \\../                     \\../ |      |      " << std::endl;
    std::cout << "   |      |                               |      |       \n" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I am thinking of?\n";
    std::cout << std::endl;
    return;
}


void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        
        FText Guess = GetValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        
        std::cout << "Bulls: " << BullCowCount.Bulls;
        std::cout << ". Cows: " << BullCowCount.Cows << "\n\n";
        
    }
    
    PrintGameSummary();
    
    return;
}


FText GetValidGuess()
{
    
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    
    do
    {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter " << BCGame.GetHiddenWordLength() << " letters.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter only lowercase letters.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please do not enter any repeating letters.\n\n";
                break;
            default:
                break;
        }
        
    } while (Status != EGuessStatus::OK);
    
    return Guess; // because xcode wants this here
}


bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "CONGRATULATIONS! You guessed the word and won the game!\n\n";
    }
    else
    {
        std::cout << "Why are you so bad at games?\n\n";
    }
    
}




