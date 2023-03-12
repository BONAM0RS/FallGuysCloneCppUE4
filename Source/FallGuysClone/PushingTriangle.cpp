
#include "PushingTriangle.h"

#include "Components/BoxComponent.h"


APushingTriangle::APushingTriangle()
{
	BoxComponent1 = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox1"));
	BoxComponent1->SetupAttachment(StaticMeshComponent);

	BoxComponent2 = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox2"));
	BoxComponent2->SetupAttachment(StaticMeshComponent);

	BoxComponent3 = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox3"));
	BoxComponent3->SetupAttachment(StaticMeshComponent);

	BoxComponent4 = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox4"));
	BoxComponent4->SetupAttachment(StaticMeshComponent);
}


void APushingTriangle::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent1->OnComponentBeginOverlap.AddDynamic(this, &APushingActor::OnActorBeginOverlap);
	BoxComponent2->OnComponentBeginOverlap.AddDynamic(this, &APushingActor::OnActorBeginOverlap);
	BoxComponent3->OnComponentBeginOverlap.AddDynamic(this, &APushingActor::OnActorBeginOverlap);
	BoxComponent4->OnComponentBeginOverlap.AddDynamic(this, &APushingActor::OnActorBeginOverlap);
}


void APushingTriangle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



