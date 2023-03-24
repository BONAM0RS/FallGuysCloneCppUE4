
#include "ActorSpawner.h"

#include "PhysicsActor.h"


AActorSpawner::AActorSpawner()
	: FirstSpawnTime       { -1 },
	  RespawnTime          { 5 },
	  IsRespawnLoop        { false },
	  IsScaleAfterSpawn    { false },
	  ScaleTimeRate        { 0.1f },
	  ScaleAddRate         { 0.1f },
	  IsPushAfterSpawn     { false },
	  IsMassEffected       { false },
      IsRandomImpulseDirY  { false },
	  MinRandomImpulseDirY { 0.0f },
	  MaxRandomImpulseDirY { 0.0f },
      ImpulseDirection     {-1.0f, 0.0f ,0.0f },
	  ImpulsePower         { 1000 }
{
	StaticMeshComponent->SetCollisionProfileName("NoCollision");
	StaticMeshComponent->bHiddenInGame = true;
}


void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!ActorClassToSpawn)
	{
		return;
	}

	//if (HasAuthority())
	{
		StartRespawnTimer();
	}
}


void AActorSpawner::StartRespawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AActorSpawner::SpawnActor, RespawnTime, IsRespawnLoop, FirstSpawnTime);
}

void AActorSpawner::ClearRespawnTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
}


void AActorSpawner::SpawnActor()
{
	AActor* SpawnedActor = nullptr;
	FTransform SpawnerTransform = GetActorTransform();

	if (!IsScaleAfterSpawn)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnerTransform);
		
		if (IsPushAfterSpawn) {
			PushActor(SpawnedActor);
		}
	}
	else if (IsScaleAfterSpawn)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnerTransform.GetLocation(), SpawnerTransform.GetRotation().Rotator());
		StartScaleTimer(SpawnedActor);
	}
}


void AActorSpawner::PushActor(AActor* Actor)
{
	APhysicsActor* PhysicsActor = Cast<APhysicsActor>(Actor);
	if (PhysicsActor)
	{
		if (IsRandomImpulseDirY) {
			ImpulseDirection.Y = FMath::RandRange(MinRandomImpulseDirY, MaxRandomImpulseDirY);
		}
		PhysicsActor->GetMesh()->AddImpulse(ImpulseDirection * ImpulsePower, NAME_None, IsMassEffected);
	}
}


void AActorSpawner::StartScaleTimer(AActor* Actor)
{
	FTimerDelegate ScaleActorDelegate = FTimerDelegate::CreateUObject(this, &AActorSpawner::ScaleActor, Actor);
	GetWorld()->GetTimerManager().SetTimer(ScaleTimerHandle, ScaleActorDelegate, ScaleTimeRate, true, 0.0f);
}

void AActorSpawner::ClearScaleTimer(AActor* Actor)
{
	GetWorld()->GetTimerManager().ClearTimer(ScaleTimerHandle);

	APhysicsActor* PhysicsActor = Cast<APhysicsActor>(Actor);
	if (PhysicsActor)
	{
		PhysicsActor->GetMesh()->SetSimulatePhysics(true);
		FBodyInstance* BodyInstance = PhysicsActor->GetMesh()->GetBodyInstance();
		BodyInstance->UpdateMassProperties();
	}
	
	if (IsPushAfterSpawn) {
		PushActor(Actor);
	}
}


void AActorSpawner::ScaleActor(AActor* Actor)
{
	FVector SpawnedActorScale = Actor->GetActorScale3D();
	FVector SpawnerTargetScale = GetActorScale3D();
	
	if (SpawnedActorScale.X < SpawnerTargetScale.X)
	{
		SpawnedActorScale += FVector(ScaleAddRate);
		Actor->SetActorScale3D(SpawnedActorScale);
	}
	else
	{
		ClearScaleTimer(Actor);
	}
}






