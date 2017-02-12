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


	ForwardForce = 10000.f;
	SidewaysForce = 10000.f;
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

}

// Called to bind functionality to input
void AHovershipBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AHovershipBase::MoveForward);
	InputComponent->BindAxis("MoveSideways", this, &AHovershipBase::MoveSideways);
}

void AHovershipBase::MoveForward(float Value) {
	FVector v = Box->GetForwardVector() * Value * ForwardForce;
	Box->AddForce(v);
}

void AHovershipBase::MoveSideways(float Value) {
	FVector v = Box->GetRightVector() * Value * SidewaysForce;
	Box->AddForce(v);
}