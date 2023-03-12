
#include "PhysicsActor.h"

#include "FallGuysCharacter.h"



APhysicsActor::APhysicsActor()
{
	//StaticMeshComponent->SetSimulatePhysics(true);
	//StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
}


void APhysicsActor::BeginPlay()
{
	Super::BeginPlay();
}


void APhysicsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APhysicsActor::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFallGuysCharacter* Character = Cast<AFallGuysCharacter>(OtherActor);
	if (Character)
	{
		Character->ActivateRagdoll();
	}
}