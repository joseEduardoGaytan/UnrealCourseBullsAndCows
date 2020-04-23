// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    // TEXT macro to encode unreal string
    PrintLine(TEXT("Welcome to Bulls Cows Game!"));
    // Ask the user to input the guess
    PrintLine(TEXT("Guess the 4 letter word!")); // TODO: Change it for a not hardcoded variable
    PrintLine(TEXT("Press enter to continue..."));
    // Set the hidden word
    this->HiddenWord = TEXT("bird"); // Unreal can encode the string correctly;

    // TODO: Set lives
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{    
    ClearScreen();
    PrintLine(Input);

    // TODO: Check if isogram
    // CTODO:heck if correct number of characters

    if (Input == this->HiddenWord) 
    {
        PrintLine(TEXT("Congratulations you win!"));
    }
    else 
    {
        // TODO: Subtract life
        // If the user run out of lives then print a message telling the input was not correct and break the loop

        // else Sorry but your guess was not correct, please try again
        PrintLine(TEXT("Sorry but your guess is not correct, you lose!"));
    }

    //while (false) 
    //{
    //    FString HiddenWord = TEXT("bird"); // Unreal can encode the string correctly
    //    ClearScreen();
    //    if (Input == HiddenWord) 
    //    {
    //        // Congratulations you win!
    //    }
    //    else 
    //    {
    
    //    }
    //}   

}