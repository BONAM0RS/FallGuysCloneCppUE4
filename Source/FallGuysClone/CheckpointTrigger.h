
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointTrigger.generated.h"

class UBoxComponent;

UCLASS()
class FALLGUYSCLONE_API ACheckpointTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpointTrigger();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent;

	bool IsActivated;
};
