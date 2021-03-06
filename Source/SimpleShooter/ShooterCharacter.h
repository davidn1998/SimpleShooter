// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditAnywhere)
	float RotationRate = 50.f;
	UPROPERTY(EditAnywhere)
	float SprintMultiplier = 1.5f;
	
	bool IsSprinting = false;

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void SprintOn();
	void SprintOff();

	void Shoot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
