#include "pch.h"

void SanityChecks()
{
	if (!UWorld::Singleton())
		return;

	if (!UWorld::Singleton()->OwningGameInstance)
		return;

	if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0])
		return;

	if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController)
		return;

	if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn)
		return;

	if (!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->PlayerState)
		return;

	if (!UWorld::Singleton()->GameState)
		return;

	if (!ULevel::Singleton())
		return;

	if (!APlayerController::Singleton())
		return;

	if (!APlayerController::Singleton()->AcknowledgedPawn)
		return;

	if (!APlayerController::Singleton()->PlayerCameraManager)
		return;

	if (!UGameInstance::Singleton())
		return;

	if (!ULocalPlayer::Singleton()->PlayerController)
		return;

	if (!ULocalPlayer::Singleton()->PlayerController->AcknowledgedPawn)
		return;

	if (!ULocalPlayer::Singleton()->ViewportClient)
		return;

	if (!ULocalPlayer::Singleton()->ViewportClient->ViewModeIndex)
		return;
}

FVector AnglesToForward(FVector origin, FRotator Angles, float distance)
{
	float angle, sr, sp, sy, cr, cp, cy, PiDiv;
	PiDiv = ((float)M_PI / 180);
	angle = TORAD(Angles.Yaw);
	sy = (float)sinf(angle);
	cy = (float)cosf(angle);
	angle = TORAD(Angles.Pitch);
	sp = sinf(angle);
	cp = (float)cosf(angle);
	angle = TORAD(Angles.Yaw);
	sr = (float)sinf(angle);
	cr = (float)cosf(angle);
	FVector Final = FVector((cp * cy * distance) + origin.X, (cp * sy * distance) + origin.Y, (-sp * distance) + origin.Z);
	return Final;
}

FVector RotatePoint(FVector EntityPos, FVector LocalPlayerPos, float angle, bool* ViewCheck)
{
	float r1, r2;
	float x1, y1;

	r1 = - (EntityPos.y - LocalPlayerPos.y);
	r2 = EntityPos.x - LocalPlayerPos.x;

	float Yaw = angle - 90.0f;
	float YawToRadian = Yaw * (float)(M_PI / 180.0f);

	x1 = (float)(r2 * ((float)cos((double)YawToRadian)) - r1 * sin((double)(YawToRadian))) / 20.0f;
	y1 = (float)(r2 * (float)sin((double)YawToRadian)) - r1 * cos((double)(YawToRadian)) / 20.0f;

	*ViewCheck = y1 < 0;

	x1 *= RadarZoom;
	y1 *= RadarZoom;

	int SizeX = RadarSize / 2;
	int SizeY = RadarSize / 2;

	x1 += SizeX;
	y1 += SizeY;

	if (x1 < 5)
		x1 = 5;
	
	if (x1 > RadarSize - 5)
		x1 = RadarSize - 5;

	if (y1 < 5)
		y1 = 5;

	if (y1 > RadarSize - 5)
		y1 = RadarSize - 5;

	x1 += RadarX;
	y1 += RadarY;

	return FVector(x1, y1, 0.0f);
}

void RadarActors(FVector baseActorLocation, AActor* targetActor, APlayerController* playerController, APlayerCameraManager* playerCameraManager)
{
	auto RadarRotation = playerCameraManager->GetCameraRotation();

	bool isVisible = false;

	auto RotationPoint = RotatePoint(targetActor->K2_GetActorLocation(), baseActorLocation, RadarRotation.Y, &isVisible);



	RenderFilledRect({ RotationPoint.X, RotationPoint.Y, 0.0f }, 3, 3, { 255, 255, 255, 255 });
}