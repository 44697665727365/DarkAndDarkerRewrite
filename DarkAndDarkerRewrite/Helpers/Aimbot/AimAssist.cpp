#include "pch.h"


void Aimbot()
{
	SanityChecks();

	AActor* Target = nullptr;

	FVector targetLocation;

	GetNearestClient(&Target, &targetLocation);

	if (!targetLocation.isValid())
		return;

	if (!Target)
		return;

	FVector2D out;
	if (UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(targetLocation, out, true)) {
		RenderLine({ ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 }, out, { 255, 255, 255, 255 }, 1.0f);
	}

	auto entity = reinterpret_cast<ADCCharacterBase*>(Target);

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		auto math = (UKismetMathLibrary*)UKismetMathLibrary::StaticClass();
		auto rotation = math->FindLookAtRotation(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->PlayerCameraManager->CameraCachePrivate.POV.Location, targetLocation);
		rotation.Z = 0;

		//AimbotRotation = rotation;

		auto re = bAimSmoothness ? SmoothAngle(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->PlayerCameraManager->CameraCachePrivate.POV.Rotation, rotation) : rotation;

		UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->SetControlRotation(re);
	}
}