
#include "ActorSpawner.h"


AActorSpawner::AActorSpawner()
	: RespawnTime { 0 }
{
}

void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (ActorClassToSpawn)
	{
		StartRespawnTimer();
	}
}

void AActorSpawner::StartRespawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AActorSpawner::SpawnActor, RespawnTime, true);
}

void AActorSpawner::ClearRespawnTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
}

void AActorSpawner::SpawnActor()
{
	FTransform Transform = GetActorTransform();
	GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, Transform);
}

