
#include "TeleportTrigger.h"

#include "FallGuysCharacter.h"
#include "Components/BoxComponent.h"


ATeleportTrigger::ATeleportTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetMobility(EComponentMobility::Static);
}


void ATeleportTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleportTrigger::OnActorBeginOverlap);
}

void ATeleportTrigger::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) {
		return;
	}
	
	AFallGuysCharacter* Character = Cast<AFallGuysCharacter>(OtherActor);
	if (Character) {
		Character->TeleportOnCheckpointPosition();
	}
}



