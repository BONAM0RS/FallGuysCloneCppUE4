
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
	void StartRespawnTimer();
	void ClearRespawnTimer();
	
	void SpawnActor();

	void PushActor(AActor* Actor);
	
	void StartScaleTimer(AActor* Actor);
	void ClearScaleTimer(AActor* Actor);
	
	UFUNCTION()
	void ScaleActor(AActor* Actor);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float FirstSpawnTime;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float RespawnTime;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	bool IsRespawnLoop;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	bool IsScaleAfterSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float ScaleTimeRate;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float ScaleAddRate;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	bool IsPushAfterSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	bool IsMassEffected;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	bool IsRandomImpulseDirY;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float MinRandomImpulseDirY;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float MaxRandomImpulseDirY;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	FVector ImpulseDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Settings")
	float ImpulsePower;
	
	FTimerHandle RespawnTimerHandle;
	FTimerHandle ScaleTimerHandle;
};









