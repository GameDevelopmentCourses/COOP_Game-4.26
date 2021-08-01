// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"

#include "DrawDebugHelpers.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
    //Actual Gun Mesh
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void APlayerWeapon::fire()
{
	
	AActor *MyOwner = GetOwner();
	

	if(MyOwner)
	{
		
		//Getting player eye height
		FVector StartLocation;
		FRotator StartRotation;
		MyOwner->GetActorEyesViewPoint(StartLocation,StartRotation);
        float RandomDistanceValue=1000;
		
        FVector EndLocation=StartLocation+StartRotation.Vector()*RandomDistanceValue;

		FCollisionQueryParams MyQueryParams;
		MyQueryParams.AddIgnoredActor(MyOwner);
		MyQueryParams.AddIgnoredActor(this);
		FHitResult Hit;
		//FString NameOfOwner = MyOwner->GetName();
		if(GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation,ECC_Visibility))
		{
			//UE_LOG(LogTemp,Log,TEXT("name:%s"),*MyOwner->GetName());
		
		}
		DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Blue,false,1,0,1);
	}
	
	FVector StartLocation_LineTrace;
	
}
