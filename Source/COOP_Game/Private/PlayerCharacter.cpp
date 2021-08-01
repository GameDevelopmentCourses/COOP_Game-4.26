// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Attached to SpringArm
	
	//Spring Arm for Camera 
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponet"));
	//SpringArmComp->SetupAttachment(RootComponent);
	
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

    ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//axis are used for button press event that are analog in nature (means dependent on some value there output changes)
	//Movement of Character
	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharacter::MoveRight);


	//Mouse control
	PlayerInputComponent->BindAxis("LookUp",this,&APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn",this,&APlayerCharacter::AddControllerYawInput);

	//This are digital in nature 
	//Crouch
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&APlayerCharacter::BeginCrouch);
    PlayerInputComponent->BindAction("Crouch",IE_Released,this,&APlayerCharacter::EndCrouch);

	//Jump
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharacter::BeginJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharacter::EndJump);
}

FVector APlayerCharacter::GetPawnViewLocation() const
{
	FVector2D TextSize = (2,2);
	//Search for camera 
	if(CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	//If camera is not present use the default function
    //return CameraComp->GetComponentLocation();
	return Super::GetPawnViewLocation();
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Movement
void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector()*Value);
	
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector()*Value);
}

//Crouch
void APlayerCharacter::BeginCrouch()
{
	Crouch();
}

void APlayerCharacter::EndCrouch()
{
	UnCrouch();
}

//Jump
void APlayerCharacter::BeginJump()
{
	Jump();
}

void APlayerCharacter::EndJump()
{
	StopJumping();
}


