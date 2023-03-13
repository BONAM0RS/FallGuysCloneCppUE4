
#include "DestroyTrigger.h"

#include "Components/BoxComponent.h"
#include "PhysicsActor.h"


ADestroyTrigger::ADestroyTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetMobility(EComponentMobility::Static);
}

void ADestroyTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestroyTrigger::OnActorBeginOverlap);
}

void ADestroyTrigger::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) {
		return;
	}
	
	APhysicsActor* PhysicsActor = Cast<APhysicsActor>(OtherActor);
	if (PhysicsActor) {
		PhysicsActor->Destroy();
	}
}

