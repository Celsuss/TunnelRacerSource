// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "ThrusterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TUNNELRACER_API UThrusterComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThrusterComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	bool UseThruster();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoverShip)
	float MaxHoverLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoverShip)
	float ThrusterForce;

	FVector PreviousForce;
};
