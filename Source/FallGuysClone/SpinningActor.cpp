
#include "SpinningActor.h"


ASpinningActor::ASpinningActor()
	: RotationRate { 0.0f, 0.0f, 0.0f }
{
	SpinningMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinningMesh"));
	SpinningMeshComponent->SetupAttachment(StaticMeshComponent);
	SpinningMeshComponent->SetMobility(EComponentMobility::Movable);

	// Enable it for actors which must push character
	bReplicates = false;
	SpinningMeshComponent->SetIsReplicated(false);
}


void ASpinningActor::BeginPlay()
{
	Super::BeginPlay();
}


void ASpinningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = SpinningMeshComponent->GetRelativeRotation();
	CurrentRotation += RotationRate * DeltaTime;
	SpinningMeshComponent->SetRelativeRotation(CurrentRotation);
}
















