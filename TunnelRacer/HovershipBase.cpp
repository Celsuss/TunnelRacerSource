// Fill out your copyright notice in the Description page of Project Settings.

#include "TunnelRacer.h"
#include "HovershipBase.h"


// Sets default values
AHovershipBase::AHovershipBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	RootComponent = Box;
	Box->SetEnableGravity(false);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Cam = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Cam->SetupAttachment(SpringArm);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	//Mesh->bComponentUseFixedSkelBounds = true;

	Thruster_fr = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_fr"));
	Thruster_fr->SetupAttachment(RootComponent);

	Thruster_fl = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_fl"));
	Thruster_fl->SetupAttachment(RootComponent);
	
	Thruster_br = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_br"));
	Thruster_br->SetupAttachment(RootComponent);
	
	Thruster_bl = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_bl"));
	Thruster_bl->SetupAttachment(RootComponent);

	CustomGravity = CreateDefaultSubobject<UCustomGravityComponent>(FName("CustomGravity"));
	CustomGravity->SetupAttachment(RootComponent);

	ForwardForce = 15000.f;
	HorizontalForce = 90000.f;
	TorquesForce = 10000.f;
	HorizontalDamping = 100000.f;
	GravityForce = -980.0f;
	m_ForwardDirection = FVector(1, 0, 0);
}

// Called when the game starts or when spawned
void AHovershipBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHovershipBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	Thruster_fr->UseThruster();
	Thruster_fl->UseThruster();
	Thruster_br->UseThruster();
	Thruster_bl->UseThruster();

	m_ForwardDirection = CustomGravity->m_ForwardVector;
	FRotator rot = FRotationMatrix::MakeFromX(m_ForwardDirection).Rotator();
	//this->FaceRotation(rot);
	//Box->SetWorldRotation(m_ForwardDirection);
	//Box->SetRelativeRotation(rot);
}

// Called to bind functionality to input
void AHovershipBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AHovershipBase::MoveForward);
	InputComponent->BindAxis("MoveSideways", this, &AHovershipBase::MoveHorizontal);
	InputComponent->BindAxis("Torque", this, &AHovershipBase::Torque);
}

void AHovershipBase::MoveForward(float Value) {
	
	FVector v =  m_ForwardDirection * Value * ForwardForce;
	Box->AddForce(v);
	//m_ForwardDirection.Z = 0;
	//UE_LOG(LogTemp, Log, TEXT("Forward direction %s"), *Box->GetForwardVector().ToString());
	
}

void AHovershipBase::MoveHorizontal(float Value) {
	if (Value == 0) {
		FVector damping = Box->GetRightVector() * Box->GetComponentVelocity() * (HorizontalDamping * -1);
		//Box->AddForce(damping);

		/*FVector force = Box->GetPhysicsLinearVelocity();
		force *= Box->GetRightVector() * 0.25;
		Box->SetPhysicsLinearVelocity(force);*/

	}
	else {
		FVector v = Box->GetRightVector() * Value * HorizontalForce;
		Box->AddForce(v);
	}
}

void AHovershipBase::Torque(float Value) {
	Box->AddTorque(FVector(0, 0, Value * TorquesForce));
}