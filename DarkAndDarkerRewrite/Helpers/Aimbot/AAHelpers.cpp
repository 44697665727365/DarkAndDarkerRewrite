#include "pch.h"
#include <vector>
#include <random>
#include <math.h>

bool InBounds(const FVector& point, const FVector2D& circleCenter, float circleRadius)
{
	FVector2D screen;
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(point, screen, true))
		return false;

	float distance = std::sqrt((screen.x - circleCenter.x) * (screen.x - circleCenter.x) +
		(screen.y - circleCenter.y) * (screen.y - circleCenter.y));

	return distance <= circleRadius;
}

void GetNearestClient(AActor** target, FVector* targetLocation)
{
	float currentDistance = FLT_MAX;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	auto Levels = UWorld::Singleton()->Levels;

	for (auto levelIndex = 0; levelIndex < Levels.Num(); levelIndex++)
	{
		auto level = Levels[levelIndex];
		if (!level)
			continue;

		for (int index{ 0 }; index < level->Actors.Num(); index++)
		{
			auto actor = level->Actors[index];

			if (!actor)
				continue;
			if (!actor->RootComponent)
				continue;
			if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController)
				continue;


			auto mActor = reinterpret_cast<ADCPlayerCharacterBase*>(actor);
			auto mSelf = reinterpret_cast<ADCPlayerCharacterBase*>(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn);

			if (!mActor)
				continue;

			if (!actor->IsA(ADCPlayerCharacterBase::StaticClass()))
				continue;

			if (actor == mSelf)
				continue;

			FVector location;

			if (mActor->IsPlayerControlled())
			{ //Player
				switch (iAimBone)
				{
				case 0:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(Head));
					break;
				case 1:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(neck_01));
					break;
				case 2:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(spine_01));
					break;
				case 3:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(hand_l));
					break;
				case 4:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(hand_r));
					break;
				case 5:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(pelvis));
					break;
				case 6:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(foot_l));
					break;
				case 7:
					location = mActor->Mesh->GetSocketLocation(mActor->Mesh->GetBoneName(foot_r));
					break;
				}

				switch (iAimType)
				{
				case 0: //None
					bShowFOV = false;
					break;
				case 1: //FOV
					bShowFOV = true;
					if (!InBounds(location, FVector2D(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), sFOVSize))
						continue;
					break;
				case 2: //Visible
					bShowFOV = false;
					if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->LineOfSightTo(actor, { 0, 0, 0 }, true))
						continue;
					break;
				case 3: //FOV Visible
					bShowFOV = true;
					if (!InBounds(location, FVector2D(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), sFOVSize))
						continue;
					if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->LineOfSightTo(actor, { 0, 0, 0 }, true))
						continue;
					break;
				}
			}
			else {
				//Not a Player, Do Nothing
			}

			float distance = location.distance(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->PlayerCameraManager->CameraCachePrivate.POV.Location);
			if (distance < currentDistance)
			{
				targetLocation->X = location.X + actor->GetVelocity().X;
				targetLocation->Y = location.Y + actor->GetVelocity().Y;
				targetLocation->Z = location.Z + actor->GetVelocity().Z;

				*target = actor;
				currentDistance = distance;
			}
		}
	}
}

bool randomBool()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int randomNum = std::rand() % 2;
	return static_cast<bool>(randomNum);
}

float randomFloat()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(-4.5, 4.5);
	return dist(gen);
}

FRotator SmoothAngle(FRotator current_rotation, FRotator new_rotation)
{
	float smoothing = (sAimSmoothness / 80);

	auto bRandom = randomBool();
	auto fRandom = randomFloat();

	if (bAimSmoothRandom)
		smoothing = bRandom ? smoothing + fRandom : smoothing - fRandom;

	FRotator VecDelta = current_rotation - new_rotation;
	VecDelta = VecDelta.normalize();

	VecDelta.x *= smoothing;
	VecDelta.y *= smoothing;
	auto To = current_rotation - VecDelta;

	return { To.x, To.y, 0 };
}
