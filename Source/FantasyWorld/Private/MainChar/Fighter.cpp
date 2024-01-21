// Fill out your copyright notice in the Description page of Project Settings.


#include "MainChar/Fighter.h"

#include "AIHelpers.h"
#include "GameFramework/MovementComponent.h"

// Sets default values
AFighter::AFighter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AFighter::BeginPlay()
{
	Super::BeginPlay();
	initialSpeed = speed;
	if(APlayerController* Player = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::
			GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
				InputSubsystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 1);
		}
	}
	
}

// Called every frame
void AFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &AFighter::Move);
	Input->BindAction(RotateAction.Get(), ETriggerEvent::Triggered, this, &AFighter::Rotate);
	Input->BindAction(RunAction.Get(), ETriggerEvent::Triggered, this, &AFighter::Run);
	Input->BindAction(RunAction.Get(), ETriggerEvent::Completed, this, &AFighter::NotRun);}

void AFighter::Move(const FInputActionInstance& Instance)
{
	FVector2D inputValue = Instance.GetValue().Get<FVector2D>();
	FVector WorldDir = (inputValue.X * GetActorForwardVector() + inputValue.Y * GetActorRightVector()) * GetWorld()->GetDeltaSeconds();
	AddMovementInput(WorldDir,speed);
}

void AFighter::Rotate(const FInputActionInstance& Instance)
{
	FVector2D inputValue = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(inputValue.X * rotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AFighter::Run(const FInputActionInstance& Instance)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Run")));
	speed = initialSpeed + 140.0f;
}

void AFighter::NotRun(const FInputActionInstance& Instance)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Not Run")));
	speed = initialSpeed;
}



