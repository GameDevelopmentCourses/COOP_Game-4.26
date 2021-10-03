// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "GameFramework/PawnMovementComponent.h"


#pragma region PlayerComponentsSetup
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Attached to SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponet"));
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

	//This Declaration is use Built in Functions To Perform Jump & Crouch
    ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;
}
#pragma endregion PlayerComponentsSetup

#pragma region PlayerControlSetup

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//Axis Mapping:- This are Analog in nature
	//(means dependent on some value there output changes)

	//Movement of Character
	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharacter::MoveRight);

	//Mouse control
	PlayerInputComponent->BindAxis("LookUp",this,&APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn",this,&APlayerCharacter::AddControllerYawInput);


	//Action Mapping:-This are digital in nature
	//(value either 0 or 1)

	//Crouch
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&APlayerCharacter::BeginCrouch);
    PlayerInputComponent->BindAction("Crouch",IE_Released,this,&APlayerCharacter::EndCrouch);

	//Jump
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharacter::BeginJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharacter::EndJump);

	//Camera ZoomIn and ZoomOut
	PlayerInputComponent->BindAction("Scope",IE_Pressed,this,&APlayerCharacter::CameraZoomIn);
	PlayerInputComponent->BindAction("Scope",IE_Released,this,&APlayerCharacter::CameraZoomOut);

}

#pragma endregion PlayerControlSetup

FVector APlayerCharacter::GetPawnViewLocation() const
{
	//Camera Attached To Player 
	if(CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	
	//If camera is not present use the default function
	//This Will Give Player Eye Height Location 
	return Super::GetPawnViewLocation();
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::CameraZoomIn()
{
	CameraComp->SetFieldOfView(70);
}

void APlayerCharacter::CameraZoomOut()
{
	CameraComp->SetFieldOfView(90);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region PlayerControlActions 
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
#pragma endregion PlayerControlActions

