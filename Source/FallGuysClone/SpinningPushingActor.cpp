
#include "SpinningPushingActor.h"

ASpinningPushingActor::ASpinningPushingActor()
{
	bReplicates = true;
	SpinningMeshComponent->SetIsReplicated(true);
}
