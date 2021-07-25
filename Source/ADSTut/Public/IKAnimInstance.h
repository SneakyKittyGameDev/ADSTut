// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"
#include "IKAnimInstance.generated.h"


class AADSTutCharacter;
class UCurveVector;
UCLASS()
class ADSTUT_API UIKAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UIKAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	AADSTutCharacter* Character;

	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	FTransform RelativeHandTransform;
	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	FTransform SightTransform;
	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	FTransform LeftHandTransform;

	FTransform FinalHandTransform;

	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	float AimAlpha;
	
	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	float ReloadAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TUTORIAL")
	UCurveVector* VectorCurve;

	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	FVector SwayLocation;

	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	FTransform TurningSwayTransform;
	FRotator UnmodifiedTurnRotator;
	FRotator OldRotation;

	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	FTransform RecoilTransform;
	FTransform FinalRecoilTransform;
	
	bool bInterpAiming;
	bool bIsAiming;
	bool bInterpRelativeHand;

protected:
	void SetSightTransform();
	void SetRelativeHandTransform();
	void SetFinalHandTransform();
	void SetLeftHandIK();

	void InterpAiming(float DeltaSeconds);
	void InterpRelativeHand(float DeltaSeconds);

	void MoveVectorCurve(float DeltaSeconds);
	void RotateWithRotation(float DeltaSeconds);

	void InterpFinalRecoil(float DeltaSeconds);
	void InterpRecoil(float DeltaSeconds);

public:
	void SetAiming(bool IsAiming);

	void CycledOptic();

	void Reload();

	UFUNCTION(BlueprintCallable,  Category = "TUTORIAL")
	void StopReload();

	UFUNCTION(BlueprintCallable,  Category = "TUTORIAL")
	void Fire();
};
