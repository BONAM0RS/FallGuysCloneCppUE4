
#include "SpinningActor.h"


ASpinningActor::ASpinningActor()
	: RotationRate { 0.0f, 0.0f, 0.0f }
{
	SpinningMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinningMesh"));
	SpinningMeshComponent->SetupAttachment(SceneComponent);
	SpinningMeshComponent->SetMobility(EComponentMobility::Movable);
	SpinningMeshComponent->SetCollisionProfileName("BlockAllDynamic");

	// Enable it only for actors which must push character during rotation
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
















