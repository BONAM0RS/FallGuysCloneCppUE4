
#pragma once

#include "CoreMinimal.h"
#include "PushingActor.h"
#include "PushingTriangle.generated.h"



class UBoxComponent;


UCLASS()
class FALLGUYSCLONE_API APushingTriangle : public APushingActor
{
	GENERATED_BODY()
	
public:	
	APushingTriangle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent1;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent2;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent3;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent4;
};
