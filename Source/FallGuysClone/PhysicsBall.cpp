
#include "PhysicsBall.h"

#include "Components/SphereComponent.h"

APhysicsBall::APhysicsBall()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	SphereComponent->SetupAttachment(StaticMeshComponent);
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
