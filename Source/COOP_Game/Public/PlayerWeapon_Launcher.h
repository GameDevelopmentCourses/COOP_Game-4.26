// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon_Launcher.generated.h"

UCLASS()
class COOP_GAME_API APlayerWeapon_Launcher : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon_Launcher();
	USkeletalMeshComponent *Meshcomp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
