// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "ADSTutCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class UStaticMeshComponent;
class UIKAnimInstance;

UCLASS(config=Game)
class AADSTutCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TUTORIAL")
	TArray<UStaticMeshComponent*> Optics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TUTORIAL")
	UStaticMeshComponent* CurrentOptic;
	UPROPERTY(ReplicatedUsing = OnRep_OpticIndex)
	uint8 OpticIndex;
	UFUNCTION()
	void OnRep_OpticIndex();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OpticIndex(uint8 NewIndex);
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AADSTutCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AADSTutProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* ReloadAnimation;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "TUTORIAL")
	UIKAnimInstance* TutAnimInstance;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "TUTORIAL")
	void SetAiming(bool IsAiming);
	UPROPERTY(ReplicatedUsing = OnRep_IsAiming)
	bool bIsAiming;
	UFUNCTION()
	void OnRep_IsAiming();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetAiming(bool IsAiming);
	
	UFUNCTION(BlueprintCallable, Category = "TUTORIAL")
	void CycleOptic();

	UFUNCTION(BlueprintCallable, Category = "TUTORIAL")
	void Reload();
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	/** Returns Mesh1P subobject **/
	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UStaticMeshComponent* GetCurrentOptic() const { return CurrentOptic; }

	USkeletalMeshComponent* GetFPGun() const { return FP_Gun; }
};

