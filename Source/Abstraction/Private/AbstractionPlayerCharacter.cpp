// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractionPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "DamageHandlerComponent.h"

AAbstractionPlayerCharacter::AAbstractionPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DamageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

void AAbstractionPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAbstractionPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbstractionPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FInputActionBinding* Binding;
	Binding = &PlayerInputComponent->BindAction(FName("InteractionStart"), IE_Pressed, this, &AAbstractionPlayerCharacter::StartInteraction);
	Binding = &PlayerInputComponent->BindAction(FName("InteractionCancel"), IE_Pressed, this, &AAbstractionPlayerCharacter::StopInteraction);
}

void AAbstractionPlayerCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	OnDeath(true);
}

float AAbstractionPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AAbstractionPlayerCharacter::TakeDamage Damage %.2f"), Damage);
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return Damage;
}


void AAbstractionPlayerCharacter::OnDeath(bool IsFellOut)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

void AAbstractionPlayerCharacter::StartInteraction()
{
	OnInteractionStart.Broadcast();
}

void AAbstractionPlayerCharacter::StopInteraction()
{
	OnInteractionCancel.Broadcast();
}

void AAbstractionPlayerCharacter::SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval)
{
	if (DamageHandlerComponent)
	{
		DamageHandlerComponent->TakeFireDamage(BaseDamage, DamageTotalTime, TakeDamageInterval);
	}
}