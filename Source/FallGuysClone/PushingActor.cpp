
#include "PushingActor.h"

#include "FallGuysCharacter.h"


APushingActor::APushingActor()
	: PushingVelocity { 500.0f }
{
	
}


void APushingActor::BeginPlay()
{
	Super::BeginPlay();
}


void APushingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APushingActor::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) {
		return;
	}
	
	AFallGuysCharacter* Character = Cast<AFallGuysCharacter>(OtherActor);
	if (Character)
	{
		FVector PushDirection = Character->GetActorLocation() - GetActorLocation();
		PushDirection.Normalize();
		
		Character->LaunchCharacter(PushDirection * PushingVelocity, false, false);
	}
}

