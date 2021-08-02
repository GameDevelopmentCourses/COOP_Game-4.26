// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class COOP_GAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Character control functions 
	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	void BeginJump();

	void EndJump();

	//Camera
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	UCameraComponent *CameraComp;

	//SpringArm
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	USpringArmComponent *SpringArmComp;

    
    	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Overriding a Default func to get Camera Location along with Eye Height Location
	virtual FVector GetPawnViewLocation() const override;

};



