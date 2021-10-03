#include "PlayerWeapon.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#pragma region WeaponComponent
// Sets default values
APlayerWeapon::APlayerWeapon()
{
    PrimaryActorTick.bCanEverTick = true;
	
    //Actual Gun Mesh
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;

	//Socket placed on Gun Skeleton For MuzzleEffect
	MuzzleSocketName="MuzzleSocket";

    BulletTraceEndName ="BeamEnd";
}
#pragma endregion  WeaponComponent

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp,Warning,TEXT("working"),);
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
		
		FVector ShortDirection=StartRotation.Vector();
	    FVector EndLocation=StartLocation+ShortDirection*DistanceOfLineTrace;

		//UE_LOG(LogTemp,Warning,TEXT("EndLocation Distance:- %s"),*ShortDirection.ToString());
		

		FCollisionQueryParams MyQueryParams;
		//Ignore Player from collision
		MyQueryParams.AddIgnoredActor(MyOwner);
		//Ignore Weapon from collision
		MyQueryParams.AddIgnoredActor(this);

        //No Hit Than End Point Is Direction OF Looking
		FVector BulletTraceEndLocation=EndLocation;
		
		FHitResult Hit;
		if(GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation,ECC_Visibility))
		{
			
			//If some thing is hit by line trace than apply point damage to it 
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(),20,EndLocation,
				Hit,MyOwner->GetInstigatorController(),this,DamageType);
            //Hit Happens Than End Point Is Hit Location
			BulletTraceEndLocation=Hit.Location;
		}
		
        //Debug line Representing line Trace 
		//DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Blue,false,1,0,1);

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
			//Checking If Hit Actor Has Damage Enabled 
			if(Hit.Actor->CanBeDamaged())
            {
				//Playing effect at Hit Location
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BloodEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
            }
		}
		
		//Bullet Fire Trace Effect played on GunSocket to end point
		//End Point Can be either hit point or any other point
		if(BulletTraceEffect)
		{
			//Getting Start  Location For Bullet Trace
			//Get The Gun Socket Location
			FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName); 
            //Spawn Bullet Trace Particle System And Get Particle System Component
			//This Allows Set The Target To Stretch the effect
			UParticleSystemComponent* BulletTraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BulletTraceEffect,MuzzleLocation);
			if(BulletTraceComp)
			{
				//Use This Component to Set The End Point for Particle Spwan
				BulletTraceComp->SetVectorParameter(BulletTraceEndName,BulletTraceEndLocation);
			}
		}
		
	}
}
