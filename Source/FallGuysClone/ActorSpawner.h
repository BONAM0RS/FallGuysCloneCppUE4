
#pragma once

#include "CoreMinimal.h"
#include "GameObjectActor.h"
#include "ActorSpawner.generated.h"


UCLASS()
class FALLGUYSCLONE_API AActorSpawner : public AGameObjectActor
{
	GENERATED_BODY()
	
public:
	AActorSpawner();
	
protected:
	virtual void BeginPlay() override;

private:
	void SpawnActor();
	
	void StartRespawnTimer();
	void ClearRespawnTimer();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float RespawnTime;
	
	FTimerHandle RespawnTimerHandle;
};
