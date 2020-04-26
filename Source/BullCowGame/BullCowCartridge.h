// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <unordered_set>
#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	virtual void SetupGame();
	virtual bool CheckWordLength(const FString HiddenWord, FString Input);
	virtual void WelcomePlayer();
	virtual void EndGame();
	virtual void ProcessGuess(const FString& Guess);
	virtual bool IsIsogram(const FString& Guess) const;
	virtual bool IsIsogramCourseVersion(const FString& Guess) const;
	virtual TArray<FString> GetValidWords(const TArray<FString>& WordsList) const; // is not going to change any private 
																				   //value this is why is const, 
																				   //we are not going to change any member variables
		
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 UserLives;
	bool bGameOver;	
};
