
#pragma once

#include "CoreMinimal.h"
#include "PhysicsActor.h"
#include "PhysicsBall.generated.h"

class USphereComponent;

UCLASS()
class FALLGUYSCLONE_API APhysicsBall : public APhysicsActor
{
	GENERATED_BODY()

public:	
	APhysicsBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* SphereComponent;
};
