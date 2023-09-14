#include "pch.h"
#include "SDK.h"

bool APlayerController::ProjectWorldLocationToScreen(FVector WorldLocation, FVector2D& ScreenLocation, bool bPlayerViewportRelative)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.ProjectWorldLocationToScreen");

	struct {
		FVector WorldLocation;
		FVector2D ScreenLocation;
		bool bPlayerViewportRelative;
		bool ReturnValue;
	} params;

	params.WorldLocation = WorldLocation;
	params.bPlayerViewportRelative = bPlayerViewportRelative;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	ScreenLocation = params.ScreenLocation;
	if (ScreenLocation.X == 0 && ScreenLocation.Y == 0)
		return false;

	return params.ReturnValue;
}

bool APawn::IsPlayerControlled()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.Pawn.IsPlayerControlled");

	struct {
		bool ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FString APlayerState::GetPlayerName()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.PlayerState.GetPlayerName");

	struct {
		struct FString ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FRotator AActor::K2_GetActorRotation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorRotation");

	struct {
		struct FRotator ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FVector AActor::K2_GetActorLocation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorLocation");

	struct {
		struct FVector ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

	return params.ReturnValue;
}

FVector AActor::GetVelocity()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.SkinnedMeshComponent.GetBoneIndex");

	struct {

		struct FVector return_value;
	} params;

	ProcessEvent(fn, &params);
	return params.return_value;
}

void AActor::GetActorBounds(bool bOnlyCollidingComponents, FVector& Origin, FVector& BoxExtent, bool bIncludeFromChildActors)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorBounds");

	struct {
		bool bOnlyCollidingComponents;
		struct FVector Origin;
		struct FVector BoxExtent;
		bool bIncludeFromChildActors;
	} params;

	params.bOnlyCollidingComponents = bOnlyCollidingComponents;
	params.Origin = Origin;
	params.BoxExtent = BoxExtent;
	params.bIncludeFromChildActors = bIncludeFromChildActors;

	ProcessEvent(fn, &params);

	Origin = params.Origin;
	BoxExtent = params.BoxExtent;
}

FVector USkeletalMeshComponent::GetSocketLocation(FName SkelComp)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.GetSocketLocation");

	struct {
		struct FName SkelComp;
		struct FVector return_value;
	} params;

	params.SkelComp = SkelComp;

	ProcessEvent(fn, &params);
	return params.return_value;
}

FVector USkeletalMeshComponent::GetBoneLocation(int32_t BoneIndex)
{
	return this->GetSocketLocation(this->GetBoneName(BoneIndex));
}

int32_t USkeletalMeshComponent::GetBoneIndex(FName BoneName)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.SkinnedMeshComponent.GetBoneIndex");

	struct {
		struct FName BoneName;
		int32_t return_value;
	} params;

	params.BoneName = BoneName;

	ProcessEvent(fn, &params);
	return params.return_value;
}

FName USkeletalMeshComponent::GetBoneName(int32_t BoneIndex)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.SkinnedMeshComponent.GetBoneName");

	struct {
		int32_t BoneIndex;
		struct FName return_value;
	} params;

	params.BoneIndex = BoneIndex;

	ProcessEvent(fn, &params);
	return params.return_value;
}

void APlayerController::SetControlRotation(FRotator& NewRotation)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.Controller.SetControlRotation");

	struct {
		FRotator NewRotation;
	} params;

	params.NewRotation = NewRotation;

	ProcessEvent(fn, &params);
}

bool APlayerController::LineOfSightTo(AActor* Other, FVector ViewPoint, bool bAlternateChecks)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.Controller.LineOfSightTo");

	struct
	{
		struct AActor* Other;
		struct FVector ViewPoint;
		bool bAlternateChecks;
		bool return_value;
	} params;

	params.Other = Other;
	params.ViewPoint = ViewPoint;
	params.bAlternateChecks = bAlternateChecks;

	ProcessEvent(fn, &params);
	return params.return_value;
}

bool ADCCharacterBase::IsSameTeam(FString PartyId)
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function DungeonCrawler.DCCharacterBase.IsSameTeam");

	struct
	{
		struct FString PartyId;
		bool return_value;
	} params;

	params.PartyId = PartyId;

	ProcessEvent(fn, &params);
	return params.return_value;
}

FString ADCCharacterBase::GetPartyId()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function DungeonCrawler.DCCharacterBase.GetPartyId");

	struct
	{
		FString return_value;
	} params;


	ProcessEvent(fn, &params);
	return params.return_value;
}

FPrimaryAssetId ADCMonsterBase::GetMonsterId()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function DungeonCrawler.DCMonsterBase.GetMonsterId");

	struct
	{
		FPrimaryAssetId return_value;
	} params;


	ProcessEvent(fn, &params);
	return params.return_value;
}

float APlayerCameraManager::GetFOVAngle()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetFOVAngle");

	struct
	{
		float return_value;
	} params;


	ProcessEvent(fn, &params);
	return params.return_value;
}

FRotator APlayerCameraManager::GetCameraRotation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraRotation");

	struct
	{
		FRotator return_value;
	} params;


	ProcessEvent(fn, &params);
	return params.return_value;
}

FVector APlayerCameraManager::GetCameraLocation()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraLocation");

	struct
	{
		FVector return_value;
	} params;


	ProcessEvent(fn, &params);
	return params.return_value;
}

FInteractTargetData UInteractableTargetComponent::GetInteractTargetData()
{
	static UFunction* fn = nullptr;
	if (!fn)
		fn = UObject::FindObject<UFunction>("Function DungeonCrawler.InteractableTargetComponent.GetInteractTargetData");

	struct
	{
		FInteractTargetData return_value;
	} params;


	ProcessEvent(fn, &params);
	return params.return_value;
}
