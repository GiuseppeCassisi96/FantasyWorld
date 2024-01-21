// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Fighter.generated.h"

UCLASS()
class FANTASYWORLD_API AFighter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category= "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Input")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category= "Input")
	TSoftObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category= "Input")
	TSoftObjectPtr<UInputAction> RotateAction;
	UPROPERTY(EditDefaultsOnly, Category= "Input")
	TSoftObjectPtr<UInputAction> RunAction;
	UPROPERTY(EditDefaultsOnly, Category= "Movement")
	float speed = 20.0f;
	UPROPERTY(EditDefaultsOnly, Category= "Movement")
	float rotationSpeed = 10.0f;
	float initialSpeed;
	// Sets default values for this character's properties
	AFighter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionInstance& Instance);
	void Rotate(const FInputActionInstance& Instance);
	void Run(const FInputActionInstance& Instance);
	void NotRun(const FInputActionInstance& Instance);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
