
#include "FallGuysCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


AFallGuysCharacter::AFallGuysCharacter()
	: DefaultMeshRelativeLocation { 0.0f, 0.0f, -97.0f },
	  DefaultMeshRelativeRotation { 0.0f, 270.0f, 0.0f },
	  IsRagdollActivated { false },
	  CheckpointLocation { 0.0f, 0.0f, 0.0f },
	  CheckpointRotation { 0.0f, 0.0f, 0.0f }
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}


//////////////////////////////////////////////////////////////////////////
// Input

void AFallGuysCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFallGuysCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFallGuysCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFallGuysCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFallGuysCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFallGuysCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFallGuysCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFallGuysCharacter::OnResetVR);
}


void AFallGuysCharacter::OnResetVR()
{
	// If FallGuysClone is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in FallGuysClone.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFallGuysCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AFallGuysCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AFallGuysCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFallGuysCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFallGuysCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFallGuysCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void AFallGuysCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Fix character collision with rotating objects
	FHitResult OutHit;
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->SafeMoveUpdatedComponent(FVector(0.f, 0.f, 0.01f), GetActorRotation(), true, OutHit);
	CharacterMovementComponent->SafeMoveUpdatedComponent(FVector(0.f, 0.f, -0.01f), GetActorRotation(), true, OutHit);
}

void AFallGuysCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateCheckpointPosition();
}


void AFallGuysCharacter::UpdateCheckpointPosition()
{
	CheckpointLocation = GetActorLocation();
	//CheckpointRotation = GetActorRotation();
}

void AFallGuysCharacter::TeleportOnCheckpointPosition()
{
	SetActorLocation(CheckpointLocation);
	SetActorRotation(CheckpointRotation);
}


void AFallGuysCharacter::ActivateRagdoll()
{
	IsRagdollActivated = true;
	
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	PlayerMesh->SetCollisionProfileName("PhysicsActor");
	PlayerMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	PlayerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlayerMesh->SetAllBodiesSimulatePhysics(true);

	StartCapsuleTimer();
	StartRespawnTimer();
}

bool AFallGuysCharacter::GetRagdollState() const
{
	return IsRagdollActivated;
}


void AFallGuysCharacter::StartCapsuleTimer()
{
	GetWorld()->GetTimerManager().SetTimer(CapsuleTimerHandle, this, &AFallGuysCharacter::DeactivateCapsule, 0.1f, false);
}

void AFallGuysCharacter::StartRespawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AFallGuysCharacter::DeactivateRagdoll, 5.0f, false);
}


void AFallGuysCharacter::DeactivateCapsule()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetTimerManager().ClearTimer(CapsuleTimerHandle);
}

void AFallGuysCharacter::DeactivateRagdoll()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	PlayerMesh->SetCollisionProfileName("CharacterMesh");

	UCapsuleComponent* PlayerCapsuleComponent = GetCapsuleComponent();
	PlayerCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	PlayerMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	PlayerMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlayerMesh->SetAllBodiesSimulatePhysics(false);

	const FVector CurrentMeshLocation = PlayerMesh->GetComponentLocation();
	PlayerCapsuleComponent->SetWorldLocation(CurrentMeshLocation);
	
	FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	AttachmentTransformRules.LocationRule = EAttachmentRule::SnapToTarget;
	PlayerMesh->AttachToComponent(PlayerCapsuleComponent, AttachmentTransformRules);
	PlayerMesh->SetRelativeLocationAndRotation(DefaultMeshRelativeLocation, DefaultMeshRelativeRotation);
	
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

	IsRagdollActivated = false;
}







