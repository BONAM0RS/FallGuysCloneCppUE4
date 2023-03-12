
#pragma once

#include "CoreMinimal.h"
#include "GameObjectActor.h"
#include "PhysicsActor.generated.h"




UCLASS()
class FALLGUYSCLONE_API APhysicsActor : public AGameObjectActor
{
	GENERATED_BODY()

public:	
	APhysicsActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult);
};
