
#include "PushingBall.h"

#include "FallGuysCharacter.h"
#include "Components/SphereComponent.h"


APushingBall::APushingBall()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	SphereComponent->SetupAttachment(StaticMeshComponent);
}


void APushingBall::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APushingBall::OnActorBeginOverlap);
}


void APushingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APushingBall::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnActorBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// White onComponentHit instead overlap
	AFallGuysCharacter* Character = Cast<AFallGuysCharacter>(OtherActor);
	if (Character)
	{
		Character->ActivateRagdoll();
	}
}