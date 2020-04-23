// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Seting Up Game
    SetupGame();

    //PrintLine(FString::Printf(TEXT("The Hidden Word is: %s"), *HiddenWord)); // Debug line we can turn it off/on as we need
    //PrintLine(TEXT("The Hidden Word is: %s.\nIt is %i characters long"), *HiddenWord, HiddenWord.Len()); // Debug line we can turn it off/on as we need -- no need of Printf
        
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
        // TEXT macro ensure cross platform compatibility in Unreal
        PrintLine(TEXT("Your guess is %s"), *Input);
        
        // Process all the game rules when the guess fails
        ProcessGuess(Input);
        
    }       
}

void UBullCowCartridge::SetupGame()
{
    // Set the hidden word
    this->HiddenWord = TEXT("bird"); // Unreal can encode the string correctly;

    // Set lives
    this->UserLives = HiddenWord.Len();
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
    PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
    PrintLine(TEXT("\nPress enter to play again\nOtherwise please hit Esc"));
}

void UBullCowCartridge::WelcomePlayer()
{
    // TEXT macro to encode unreal string
    PrintLine(TEXT("Welcome to Bulls Cows Game!"));
    // Ask the user to input the guess
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); // TODO: Change it for a not hardcoded variable   
    PrintLine(TEXT("You have %i lives!"), UserLives); // TODO: Change it for a not hardcoded variable   
    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{    
    // Using early returns; not needed but is part of a challenge
    // We can avoid nesting

    // Checking Player Guess
    if (Guess == this->HiddenWord)
    {
        PrintLine(TEXT("Congratulations you win!"));
        EndGame();
        return;
    }

    // Validation stuff

    // 1. Check if correct number of characters
    bool bHasCorrectNumberOfChars = this->CheckWordLength(this->HiddenWord, Guess);

    if (!bHasCorrectNumberOfChars)
    {
        PrintLine(TEXT("Sorry but the Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        PrintLine(TEXT("You still have %i lives remain!"), UserLives);
        return;
    }

    // TODO:2. Check if isogram
    // bool bIsIsogram = this->IsIsogram(Input);
    // Check if not Isogram

    // If the Player doesn't hit the Hidden word then the user lose a life
    // Subtract life
    --UserLives;

    // If the user has no any lives left then the user lose
    if (UserLives <= 0) 
    {
        PrintLine(TEXT("Sorry but you lose, you don't have any lives left!"));
        EndGame();
        return;
    }

    // Show the player the Bulls and Cows

    // Print the additional or lives regarding information to the user
    PrintLine(TEXT("Sorry but your guess is not correct, please try again!"));
    PrintLine(TEXT("You have %i lives remain!"), UserLives);

}