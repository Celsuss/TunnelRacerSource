// Fill out your copyright notice in the Description page of Project Settings.

#include "TunnelRacer.h"
#include "CustomGravityComponent.h"


// Sets default values for this component's properties
UCustomGravityComponent::UCustomGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	m_Box = (UBoxComponent*)GetAttachmentRoot();
	//m_Box->SetEnableGravity(false);
	GravityForce = -980.0f;
}


// Called when the game starts
void UCustomGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//m_Box->SetEnableGravity(false);
	m_Box = (UBoxComponent*)GetAttachmentRoot();
	m_ForwardVector = FVector(1, 0, 0);
}


// Called every frame
void UCustomGravityComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	FHitResult* hit = new FHitResult();

	const FVector start = GetComponentLocation();
	const FVector end = start - m_Box->GetUpVector() * 1000;

	FCollisionQueryParams* traceParams = new FCollisionQueryParams();
	traceParams->AddIgnoredActor(GetOwner());

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility, *traceParams)) {
		DrawDebugLine(GetWorld(), start, start+ (hit->ImpactNormal*200), FColor(0, 0, 255), false, -1, 0, 2);
		
		FVector g = hit->ImpactNormal * m_Box->GetMass() * GravityForce;
		m_Box->AddForce(g);

		m_ForwardVector = hit->ImpactNormal.RotateAngleAxis(90, m_Box->GetRightVector());
		DrawDebugLine(GetWorld(), hit->ImpactPoint, hit->ImpactPoint + m_ForwardVector * 500, FColor(255, 0, 0), false, -1, 0, 2);
	}
	else
		DrawDebugLine(GetWorld(), start, start + (end), FColor(0, 0, 255), false, -1, 0, 2);
}

