#pragma once
#include "pch.h"

bool InBounds(const FVector& point, const FVector2D& circleCenter, float circleRadius);
void GetNearestClient(AActor** target, FVector* targetLocation);
bool randomBool();
float randomFloat();
FRotator SmoothAngle(FRotator current_rotation, FRotator new_rotation);
