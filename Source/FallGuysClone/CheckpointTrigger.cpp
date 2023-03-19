
#include "CheckpointTrigger.h"

#include "FallGuysCharacter.h"
#include "Components/BoxComponent.h"


ACheckpointTrigger::ACheckpointTrigger()
	: IsActivated { false }
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetMobility(EComponentMobility::Static);
}


void ACheckpointTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointTrigger::OnActorBeginOverlap);
}

void ACheckpointTrigger::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) {
		return;
	}

	if (IsActivated == true) {
		return;
	}

	AFallGuysCharacter* Character = Cast<AFallGuysCharacter>(OtherActor);
	if (Character) {
		Character->UpdateCheckpointPosition();
		IsActivated = true;
	}
}

