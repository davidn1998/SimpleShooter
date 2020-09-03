// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "kismet/GameplayStatics.h"
#include "particles/ParticleSystem.h"

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	MuzzleFlash = CreateDefaultSubobject<UParticleSystem>(TEXT("Muzzle Flash"));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger() 
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) {return;}

	AController* OwnerController = OwnerPawn->GetController();
	if(!OwnerController) {return;}

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);

	// DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f, 2, FColor::Red, true);

	FVector End = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	if(GetWorld()->LineTraceSingleByChannel(OUT Hit, ViewPointLocation, End, ECollisionChannel::ECC_GameTraceChannel1, TraceParams))
	{
		// DrawDebugLine(GetWorld(), ViewPointLocation, Hit.Location, FColor::Red, true);
		DrawDebugPoint(GetWorld(), Hit.Location, 20.f, FColor::Red, true);
	}
}

