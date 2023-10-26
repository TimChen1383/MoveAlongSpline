// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "MoveAlongSpline.generated.h"

UCLASS()
class UECPP_PRACTICE_API AMoveAlongSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveAlongSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Move Along Spline")
	UStaticMeshComponent* PlatformMesh = nullptr;

	UPROPERTY(EditAnywhere, Category="Move Along Spline")
	USplineComponent* Splinepath = nullptr;

	UPROPERTY(EditAnywhere, Category="Move Along Spline")
	UCurveFloat* TimeCurveFloat = nullptr;
	
	FVector BoxDetectSize = FVector(80,80,80);

	UPROPERTY(EditAnywhere, Category="Move Along Spline")
	float PlatformSpeed = 1.0f;
	
	UBoxComponent* BoxDetection;

	FTimeline Timeline;

	UFUNCTION()
	void MovingPlatform(float Value);

	UFUNCTION()
	void MovingForward(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void MovingBackward(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	USceneComponent* SceneComponent;

};


//Create platform, create spline
//create curve float
//create FTimeLine
//add timeline movement to the tick
//FTimeLine add interp float and interp progress value
//On platform begin overlap > add dynamic delegate, moving event
//On platform end overlap > add dynamic delegate, reverse event
//Define moving event
	//play timeline
	//get the timeline progress value
	//use timeline progress value run get location and rotation along spline
	//set object position and rotation
//Define reverse event
	//reverse timeline
	//get the timeline progress value
	//use timeline progress value run get location and rotation along spline
	//set object position and rotation
