// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <algorithm>
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h" // this is supposed to be contained on CoreMinimal.h


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
        
    //// Referencia
    //int32 a = 0;
    //int32 b = 5;
    //int32& refa = a;

    //PrintLine(TEXT("a = %i; b = %i; c = %i"), a,b,refa);
    //refa = b; // This is going to change a because refa is a reference to a
    //PrintLine(TEXT("a = %i; b = %i; c = %i"), a, b, refa);
        
    // Seting Up Game
    SetupGame();

    //PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); // Debug line we can turn it off/on as we need
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
    // Get a random word from Valid words
    TArray<FString> ValidWords = GetValidWords(Words);
    int32 RandomIndex = FMath::RandRange(0, ValidWords.Num() - 1);
    this->HiddenWord = ValidWords[RandomIndex]; // Unreal can encode the string correctly;

    // Set lives
    this->UserLives = HiddenWord.Len() * 2;
    bGameOver = false;

    WelcomePlayer();

    PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); // Debug line we can turn it off/on as we need
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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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

    // 2. Check if isogram
    bool bIsIsogram = this->IsIsogram(Guess);
    
    if (!bIsIsogram) 
    {
        PrintLine(TEXT("Sorry but no repeating letters, please try again!"));
        PrintLine(TEXT("You still have %i lives remain!"), UserLives);
        return;
    }
                
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
    // are not initialized this means are out parameters
    int32 Bulls, Cows;
    this->GetBullCows(Guess, Bulls, Cows);

    // Print the additional or lives regarding information to the user
    PrintLine(TEXT("Sorry but your guess is not correct, please try again!"));
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Bulls, Cows);
    PrintLine(TEXT("You have %i lives remain!"), UserLives);

}

bool UBullCowCartridge::IsIsogram(const FString& Guess) const
{
    // Since a set doesn't allow any repeated values
    std::unordered_set<char> Chars;

    // we evaluate that all conditions are met for the predicate
    // if the word is not an isogram then it will fail in the attempt to insert in the set
    bool bIsIsogram = std::all_of(
        Guess.begin(),
        Guess.end(),
        // since we can't use an unary predicate with two parameters we use
        // Lambda expression to use a two parameters predicate        
        [&Chars](const char GuessChar)
        {         
            // Check for duplicate in the unordered set
            // we call second and if is a duplicate it will return false
            // this will invalidate the all_of method
            return Chars.insert(GuessChar).second;            
        }
    );
            
    return bIsIsogram;
}

bool UBullCowCartridge::IsIsogramCourseVersion(const FString& Guess) const
{    
    for (int32 Index = 0; Index < Guess.Len() - 1; Index++)
    {
        char characterTaken = Guess[Index];
        for (int32 Comparison = Index + 1; Comparison < Guess.Len(); Comparison++)
        {
            if (characterTaken == Guess[Comparison])
            {
                return false;
            }
        }
    }    

    return true;
}

/// Is const because is not going to change the state of the class. Any member variables
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString hiddenWord : WordList)
    {        
        int32 wordLength = hiddenWord.Len();
        if (wordLength >= 4 && wordLength <= 8)
        {
            bool bIsIsogram = IsIsogram(hiddenWord);
            if (bIsIsogram)
            {
                // Add element to the TArray, Emplace is recommended for this
                ValidWords.Emplace(hiddenWord);
            }
        }
    }

    /*for (int32 Index = 0; Index < ValidWords.Num(); Index++)
    {
        PrintLine(TEXT("%s."), *ValidWords[Index]);
    }*/

    return ValidWords;

}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    // initialize out parameter, because this are not initialized outside the function
    BullCount = 0;
    CowCount = 0;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        char GuessChar = Guess[GuessIndex];
        if (GuessChar == this->HiddenWord[GuessIndex])
        {
            BullCount++;
            continue; // next iteration
        }

        for (int32 HiddenWordIndex = 0; HiddenWordIndex < HiddenWord.Len(); HiddenWordIndex++)
        {
            char HiddenWordChar = HiddenWord[HiddenWordIndex];
            if (GuessChar == HiddenWordChar)
            {
                CowCount++;
                break;
            }
        }

    }

}
