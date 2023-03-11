
#pragma once

#include "CoreMinimal.h"
#include "GameObjectActor.h"
#include "PushingActor.generated.h"


UCLASS()
class FALLGUYSCLONE_API APushingActor : public AGameObjectActor
{
	GENERATED_BODY()
	
public:	
	APushingActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	virtual void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Custom Actor Settings")
	float PushingVelocity;
};
