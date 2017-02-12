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

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Thruster_fr = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_fr"));
	Thruster_fr->SetupAttachment(RootComponent);

	Thruster_fl = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_fl"));
	Thruster_fl->SetupAttachment(RootComponent);
	
	Thruster_br = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_br"));
	Thruster_br->SetupAttachment(RootComponent);
	
	Thruster_bl = CreateDefaultSubobject<UThrusterComponent>(FName("ThrusterComponent_bl"));
	Thruster_bl->SetupAttachment(RootComponent);


	ForwardForce = 15000.f;
	HorizontalForce = 30000.f;
	TorquesForce = 10000.f;
	HorizontalDamping = 60000.f;
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
	if (Thruster_fr->UseThruster() && Thruster_fl->UseThruster()) {
		m_ForwardDirection = Thruster_fr->m_GroundNormal;

		if (Thruster_br->UseThruster() && Thruster_bl->UseThruster()) {
			m_ForwardDirection = Thruster_br->m_GroundNormal;
			UE_LOG(LogTemp, Log, TEXT("Forward direction %s"), *m_ForwardDirection.ToString());
		}
	}

	FVector g = Box->GetUpVector() * Box->GetMass() * GravityForce;
	Box->AddForce(g);
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
	FVector v = m_ForwardDirection * Value * ForwardForce;
	Box->AddForce(v);
}

void AHovershipBase::MoveHorizontal(float Value) {
	if (Value == 0) {
		FVector damping = -(Box->GetRightVector() * Box->GetComponentVelocity().Y * HorizontalDamping);
		Box->AddForce(damping);
	}
	else {
		FVector v = Box->GetRightVector() * Value * HorizontalForce;
		Box->AddForce(v);
	}
}

void AHovershipBase::Torque(float Value) {
	Box->AddTorque(FVector(0, 0, Value * TorquesForce));
}