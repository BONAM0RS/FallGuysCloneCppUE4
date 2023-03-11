
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameObjectActor.generated.h"


UCLASS()
class FALLGUYSCLONE_API AGameObjectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameObjectActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
};
