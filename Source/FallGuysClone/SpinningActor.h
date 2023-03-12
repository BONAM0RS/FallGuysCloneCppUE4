
#pragma once

#include "CoreMinimal.h"
#include "GameObjectActor.h"
#include "SpinningActor.generated.h"


UCLASS()
class FALLGUYSCLONE_API ASpinningActor : public AGameObjectActor
{
	GENERATED_BODY()

public:	
	ASpinningActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* SpinningMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Settings")
	FRotator RotationRate;
};
