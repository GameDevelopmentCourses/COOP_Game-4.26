#include "PlayerWeapon.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
    PrimaryActorTick.bCanEverTick = true;
	
    //Actual Gun Mesh
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;

	//Socket placed on Gun Skeleton For MuzzleEffect
	MuzzleSocketName="MuzzleSocket";
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

//This Fire Function Is Called In Blueprint
//Later this would be transfer to c++ in character class
void APlayerWeapon::Fire()
{
	
	AActor *MyOwner = GetOwner();
	
	if(MyOwner)
	{	
		//Getting Position of the Camera or Player eye height
		FVector StartLocation;
		FRotator StartRotation;
		MyOwner->GetActorEyesViewPoint(StartLocation,StartRotation);

		//LineTrace Length
		float DistanceValue=1000;
		FVector ShortDirection=StartRotation.Vector();
	    FVector EndLocation=StartLocation+ShortDirection*DistanceValue;

		FCollisionQueryParams MyQueryParams;
		//Ignore Player from collision
		MyQueryParams.AddIgnoredActor(MyOwner);
		//Ignore Weapon from collision
		MyQueryParams.AddIgnoredActor(this);

		FHitResult Hit;
		if(GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation,ECC_Visibility))
		{
			//If some thing is hit by line trace than apply point damage to it 
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(),20,ShortDirection,
				Hit,MyOwner->GetInstigatorController(),this,DamageType);
		}
		
        //Debugline Representing line Trace 
		DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Blue,false,1,0,1);

		//Firing Effect Played on the Muzzle of Gun
		if(MuzzleEffect)
		{
			//Playing Effect on the Socket of the Gun Mesh Component
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect,MeshComp,MuzzleSocketName);
		}
		
		//Blood Spill Effect played on the Place  where line Trace is Hit
		//If Line trace Hit nothing Than Dont Play Effect
		if(BloodEffect && Hit.Actor!=nullptr)
		{
			//Playing effect at Hit Location 
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BloodEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
		}
    }
}
