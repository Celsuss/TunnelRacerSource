// Fill out your copyright notice in the Description page of Project Settings.

#include "TunnelRacer.h"
#include "ThrusterComponent.h"


// Sets default values for this component's properties
UThrusterComponent::UThrusterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
	MaxHoverLength = 60.f;
	ThrusterForce = 24000.f;
}


// Called when the game starts
void UThrusterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	PreviousForce = FVector(0, 0, 0);
}


// Called every frame
void UThrusterComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	//FHitResult* hit = new FHitResult();

	//UBoxComponent* box = (UBoxComponent*)GetAttachmentRoot();
	//const FVector start = ComponentToWorld.GetLocation();
	//const FVector end = start - box->GetUpVector() * MaxHoverLength;

	//FCollisionQueryParams* traceParams = new FCollisionQueryParams();
	//traceParams->AddIgnoredActor(GetOwner());

	////call GetWorld() from within an actor extending class
	//if (GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility, *traceParams)) {
	//	DrawDebugLine(GetWorld(), start, end, FColor(0, 255, 0), false, -1, 0, 2);

	//	const float length = (hit->ImpactPoint - start).Size() / MaxHoverLength;
	//	FVector force = FMath::Lerp(ThrusterForce, 0.f, length) * hit->ImpactNormal;
	//	const FVector deltaForce = PreviousForce - force;
	//	PreviousForce = force;
	//	force -= (deltaForce * 3);
	//	box->AddForceAtLocation(force, start);

	//	m_GroundNormal = hit->ImpactNormal.RotateAngleAxis(-90, FVector(1, 0, 0));
	//}
	//else {
	//	DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 2);
	//}
}

bool UThrusterComponent::UseThruster() {
	FHitResult* hit = new FHitResult();

	UBoxComponent* box = (UBoxComponent*)GetAttachmentRoot();
	const FVector start = ComponentToWorld.GetLocation();
	const FVector end = start - box->GetUpVector() * MaxHoverLength;

	FCollisionQueryParams* traceParams = new FCollisionQueryParams();
	traceParams->AddIgnoredActor(GetOwner());

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility, *traceParams)) {
		DrawDebugLine(GetWorld(), start, end, FColor(0, 255, 0), false, -1, 0, 2);

		const float length = (hit->ImpactPoint - start).Size() / MaxHoverLength;
		FVector force = FMath::Lerp(ThrusterForce, 0.f, length) * hit->ImpactNormal;
		const FVector deltaForce = PreviousForce - force;
		PreviousForce = force;
		force -= (deltaForce * 3);
		box->AddForceAtLocation(force, start);

		m_GroundNormal = hit->ImpactNormal.RotateAngleAxis(90, FVector(0, 1, 0));
		return true;
	}
	else {
		DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 2);
		return false;
	}
}