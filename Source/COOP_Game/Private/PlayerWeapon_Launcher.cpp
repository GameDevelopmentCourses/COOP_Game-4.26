// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon_Launcher.h"

// Sets default values
APlayerWeapon_Launcher::APlayerWeapon_Launcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Meshcomp= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshingComp"));

}

// Called when the game starts or when spawned
void APlayerWeapon_Launcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerWeapon_Launcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

