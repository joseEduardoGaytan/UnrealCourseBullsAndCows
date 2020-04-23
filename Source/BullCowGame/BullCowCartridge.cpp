// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Seting Up Game
    SetupGame();

    //PrintLine(FString::Printf(TEXT("The Hidden Word is: %s"), *HiddenWord)); // Debug line we can turn it off/on as we need
    PrintLine(TEXT("The Hidden Word is: %s.\nIt is %i characters long"), *HiddenWord, HiddenWord.Len()); // Debug line we can turn it off/on as we need -- no need of Printf
        
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{    
    ClearScreen();

    // if game is over then do ClearScreen and SetupGame()
    if (bGameOver) 
    {
        SetupGame();
    }
    // else check the Player Guess
    else
    {
        PrintLine(TEXT("Your guess is %s"), *Input);

        // Do we need to surround this on a loop? or global variables will be enough?
        // Checking Player Guess
        if (Input == this->HiddenWord)
        {
            PrintLine(TEXT("Congratulations you win!"));   
            EndGame();
        }
        else
        {
            // TODO: Validation    
            // TODO: Check if isogram
            // bool bIsIsogram = this->IsIsogram(Input);
            // check if correct number of characters
            bool bHasCorrectNumberOfChars = this->CheckWordLength(this->HiddenWord, Input);

            if (!bHasCorrectNumberOfChars)
            {
                PrintLine(TEXT("Sorry but the Hidden Word is %i characters long, try again!"), HiddenWord.Len());
            }
            else
            {
                // TODO: Subtract life
                // this->UserLifes--;
                // If the user run out of lives then print a message telling the input was not correct and break the loop
                // Ask if the user wants to play again
                // if don't then exit the game
                // else start again

                // else Sorry but your guess was not correct, please try again
                PrintLine(TEXT("Sorry but your guess is not correct, please try again!"));
            }
             
            EndGame();
        }
    }       
}

void UBullCowCartridge::SetupGame()
{
    // Set the hidden word
    this->HiddenWord = TEXT("bird"); // Unreal can encode the string correctly;

    // Set lives
    this->UserLives = 4;
    bGameOver = false;

    WelcomePlayer();
}

bool UBullCowCartridge::CheckWordLength(const FString HiddenWord, FString Input)
{
    return HiddenWord.Len() == Input.Len();
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again\nOtherwise please hit Esc"));
}

void UBullCowCartridge::WelcomePlayer()
{
    // TEXT macro to encode unreal string
    PrintLine(TEXT("Welcome to Bulls Cows Game!"));
    // Ask the user to input the guess
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); // TODO: Change it for a not hardcoded variable
    PrintLine(TEXT("Press enter to continue..."));
}