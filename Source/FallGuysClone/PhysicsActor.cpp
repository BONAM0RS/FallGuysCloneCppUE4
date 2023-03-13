
#include "PhysicsActor.h"

#include "FallGuysCharacter.h"


APhysicsActor::APhysicsActor()
	: IsDestroyTimerOn  { true },
	  DestroyTime       { 20 }
{
	SceneComponent->SetMobility(EComponentMobility::Movable);
	
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetSimulatePhysics(true);
}


void APhysicsActor::BeginPlay()
{
	Super::BeginPlay();

	if (IsDestroyTimerOn) {
		StartDestroyTimer();
	}
}


void APhysicsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APhysicsActor::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) {
		return;
	}
	
	AFallGuysCharacter* Character = Cast<AFallGuysCharacter>(OtherActor);
	if (Character)
	{
		Character->ActivateRagdoll();
	}
}


void APhysicsActor::StartDestroyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &APhysicsActor::DestroyActor, DestroyTime, false);
}

void APhysicsActor::ClearDestroyTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimerHandle);
}


void APhysicsActor::DestroyActor()
{
	ClearDestroyTimer();
	Destroy();
}