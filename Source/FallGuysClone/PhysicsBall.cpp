
#include "PhysicsBall.h"

#include "Components/SphereComponent.h"

APhysicsBall::APhysicsBall()
{
	// Disabled simulating physics to spawn this actor with scaling animation from actor spawner, enable after spawn
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetCollisionProfileName("BlockAllDynamic");
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	SphereComponent->SetupAttachment(StaticMeshComponent);
	SphereComponent->SetMobility(EComponentMobility::Movable);
}

void APhysicsBall::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APhysicsActor::OnActorBeginOverlap);
}

void APhysicsBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
