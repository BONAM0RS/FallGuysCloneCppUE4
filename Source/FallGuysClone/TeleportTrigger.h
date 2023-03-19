
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportTrigger.generated.h"

class UBoxComponent;

UCLASS()
class FALLGUYSCLONE_API ATeleportTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportTrigger();

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
};
