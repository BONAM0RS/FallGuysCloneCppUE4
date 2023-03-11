
#include "GameObjectActor.h"


AGameObjectActor::AGameObjectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComponent);
	SceneComponent->SetMobility(EComponentMobility::Static);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	StaticMeshComponent->SetMobility(EComponentMobility::Static);
}


void AGameObjectActor::BeginPlay()
{
	Super::BeginPlay();
}


void AGameObjectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

