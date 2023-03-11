
#pragma once

#include "CoreMinimal.h"
#include "PushingActor.h"
#include "PushingBall.generated.h"


class USphereComponent;

UCLASS()
class FALLGUYSCLONE_API APushingBall : public APushingActor
{
	GENERATED_BODY()

public:	
	APushingBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* SphereComponent;
};
