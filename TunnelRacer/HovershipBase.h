// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ThrusterComponent.h"
#include "HovershipBase.generated.h"

UCLASS()
class TUNNELRACER_API AHovershipBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHovershipBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float Value);

	void MoveHorizontal(float Value);

	void Torque(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UCameraComponent* Cam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UThrusterComponent* Thruster_fr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UThrusterComponent* Thruster_fl;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UThrusterComponent* Thruster_br;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=HoverShip)
	UThrusterComponent* Thruster_bl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoverShip)
	float ForwardForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoverShip)
	float HorizontalForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoverShip)
	float TorquesForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoverShip)
	float HorizontalDamping;

	FVector m_ForwardDirection;
};
