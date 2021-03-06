// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class COOP_GAME_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon();
	
    UFUNCTION(BlueprintCallable,Category="Weapon")
	void Fire();


	//Actual Gun Mesh
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	USkeletalMeshComponent* MeshComp;

	//class Declaration to Apply point Damage
	TSubclassOf<UDamageType> DamageType;

	//Socket Name For Muzzle Effect spawning Place
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Weapon")
    FName MuzzleSocketName;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Weapon")
	FName  BulletTraceEndName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	float DistanceOfLineTrace=1000;

#pragma region ParticleEffects

	//Particle For Blood Effect On Player Hit  
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	UParticleSystem* BloodEffect;

	//Particle For Muzzle Effect On Gun to Show Bullet is Firing
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	UParticleSystem* MuzzleEffect;

	//Particle For Bullet Trace Effect to Show Bullet Trajectory
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	UParticleSystem* BulletTraceEffect;

#pragma endregion ParticleEffects

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
