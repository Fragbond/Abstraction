// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractionLog.h"

// Sets default values for this component's properties
UAbstractionLog::UAbstractionLog()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Error, TEXT("UAbstractLogComponent::BeginPlay::BeginPlay %s"), *DataString);
	// ...
}


// Called when the game starts
void UAbstractionLog::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbstractionLog::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

