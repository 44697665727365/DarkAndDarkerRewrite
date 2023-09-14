#pragma once
#include "pch.h"

void SanityChecks();
FVector AnglesToForward(FVector origin, FRotator Angles, float distance);
FVector RotatePoint(FVector EntityPos, FVector LocalPlayerPos, float angle, bool* ViewCheck);
void RadarActors(FVector baseActorLocation, AActor* targetActor, APlayerController* playerController, APlayerCameraManager* playerCameraManager);