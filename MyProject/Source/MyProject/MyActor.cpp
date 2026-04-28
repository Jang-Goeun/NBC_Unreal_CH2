// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	float Distance = 0;
	int TriggerEventcount = 0;

	// 0, 0, 50에서 시작
	SetActorLocation(FVector(0, 0, 50));

	// 10회 이동
	FString DebugMessageMove = FString::Printf(TEXT("Start Move!!"));
	LogPrint(FColor::Yellow, DebugMessageMove);

	for (int32 i = 1; i <= 10; i++)
	{
		Distance += Move(i);

		// 50% 확률 이벤트 시스템 호출
		if (FMath::FRand() <= 0.5f)
		{
			TriggerEvent();
			TriggerEventcount++;
		}
	}

	// 10회 회전
	FString DebugMessageTurn = FString::Printf(TEXT("Start Turn!!"));
	LogPrint(FColor::Yellow, DebugMessageTurn);

	for (int32 i = 0; i < 10; i++)
	{
		Turn();
	}

	// 총 이동 거리와 이벤트 발생 횟수 출력
	FString DebugMessageDistance = FString::Printf(TEXT("Total Distance: %f"), Distance);
	FString DebugMessageTriggerEvent = FString::Printf(TEXT("Total TriggerEvent: %d"), TriggerEventcount);

	LogPrint(FColor::Yellow, DebugMessageDistance);
	LogPrint(FColor::Yellow, DebugMessageTriggerEvent);
}

// 이동 함수
float AMyActor::Move(int32 Step) {
	// 이전 위치 저장
	FVector PreviousLocation = GetActorLocation();

	// -50 ~ 50 까지 랜덤하게 위치 이동
	FVector Target;
	Target.X = FMath::FRandRange(-50.0, 50.0);
	Target.Y = FMath::FRandRange(-50.0, 50.0);
	Target.Z = 0;

	AddActorWorldOffset(Target);

	// 현재 위치 저장
	FVector CurrentLocation = GetActorLocation();
	
	// 몇 번째 이동인지 상태 정보 출력
	FString DebugMessage = FString::Printf(TEXT("Step %d Location: %s"), Step, *CurrentLocation.ToString());


	// 로그 출력
	LogPrint(FColor::Red, DebugMessage);

	// 이동 거리 반환
	return FVector::Dist(PreviousLocation, CurrentLocation);
}

// 회전 함수
void AMyActor::Turn()
{
	FRotator DeltaRotation;
	DeltaRotation.Yaw = FMath::FRandRange(-180.0, 180.0);
	DeltaRotation.Pitch = 0;
	DeltaRotation.Roll = 0;

	AddActorWorldRotation(DeltaRotation);

	FRotator CurrentRotation = GetActorRotation();

	// 로그 출력
	LogPrint(FColor::Red, CurrentRotation.ToString());
}

// 트리거 이벤트 함수
void AMyActor::TriggerEvent() {
	LogPrint(FColor::Green, "TriggerEvent!!");
}

// 로그 출력 함수
void AMyActor::LogPrint(FColor C, FString S) {
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30, C, S);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *S);
}