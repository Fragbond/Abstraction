// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.generated.h"

class UObjectiveComponet;
class UObjectiveHud;
class UUserWidget;

UCLASS()
class ABSTRACTION_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

	UObjectiveWorldSubsystem() {}

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

protected:

	void DisplayObjectiveWidget();
	void DisplayObjectivesCompleteWidget();

	virtual void Deinitialize() override;

	void CreateObjectiveWidget();
	void RemoveObjectiveWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);
private:
	UPROPERTY()
		UObjectiveHud* ObjectiveWidget = nullptr;
	UPROPERTY()
		UUserWidget* ObjectivesCompleteWidget = nullptr;

	//add remove them
	//sign up for callback onchanged
	TArray<const UObjectiveComponent*> Objectives;
};
