// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAlongSpline.h"

// Sets default values
AMoveAlongSpline::AMoveAlongSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up components
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Splinepath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Path"));
	BoxDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Detection"));
	Splinepath->SetGenerateOverlapEvents(false);
	BoxDetection->SetBoxExtent(BoxDetectSize);
	Splinepath->SetupAttachment(SceneComponent);
	BoxDetection->SetupAttachment(PlatformMesh);
	PlatformMesh->SetupAttachment(SceneComponent);
	PlatformMesh->SetMobility(EComponentMobility::Movable);

	//When component overlapped
	BoxDetection->OnComponentBeginOverlap.AddDynamic(this, &AMoveAlongSpline::MovingForward);
	BoxDetection->OnComponentEndOverlap.AddDynamic(this, &AMoveAlongSpline::MovingBackward);
}

// Called when the game starts or when spawned
void AMoveAlongSpline::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineFloat TimlineProgress;
	TimlineProgress.BindDynamic(this, &AMoveAlongSpline::MovingPlatform);
	Timeline.AddInterpFloat(TimeCurveFloat, TimlineProgress);
}

// Called every frame
void AMoveAlongSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);

}

void AMoveAlongSpline::MovingPlatform(float Value)
{
	float SplineLength = Splinepath->GetSplineLength();
	FVector CurrentLocation = Splinepath->GetWorldLocationAtDistanceAlongSpline(Value*SplineLength*PlatformSpeed);

	GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Hello %s"),*CurrentLocation.ToString()));
	//FRotator CurrentRotation = Splinepath->GetWorldRotationAtDistanceAlongSpline(Value*SplineLength);
	PlatformMesh->SetWorldLocation(CurrentLocation);
}

void AMoveAlongSpline::MovingForward(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(TimeCurveFloat)
	{
		Timeline.PlayFromStart();
	}
	
}

void AMoveAlongSpline::MovingBackward(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(TimeCurveFloat)
	{
		Timeline.Reverse();
	}
	
}

