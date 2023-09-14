#include "pch.h"

//FVector OriginalLocation;
//FRotator OriginalRotation;

//ViewPoint (FOV)
GetViewPoint_t GetViewPoint;
void GetViewPoint_f(ULocalPlayer* _this, FMinimalViewInfo* OutViewInfo)
{
	GetViewPoint(_this, OutViewInfo);


    static bool GetCameraLocation = true;
    static FVector NewLocation;

    if (GetCameraLocation) {
        // Set our new location to the original spot once
        NewLocation = OutViewInfo->Location;
        GetCameraLocation = false;
    }

    if (bFreeCam)
    {
        if (GetAsyncKeyState('W') & 1) NewLocation.X += 75.f;
        else if (GetAsyncKeyState('S') & 1) NewLocation.X -= 75.f;
        else if (GetAsyncKeyState('A') & 1) NewLocation.Y -= 75.f;
        else if (GetAsyncKeyState('D') & 1) NewLocation.Y += 75.f;
        else if (GetAsyncKeyState(VK_SPACE) & 1) NewLocation.Z += 75.f;
        else if (GetAsyncKeyState(VK_SHIFT) & 1) NewLocation.Z -= 75.f;

        // Modify OutViewInfo
        OutViewInfo->Location = NewLocation;
    }
	OutViewInfo->FOV = fFOV;

    APlayerController* PlayerController = _this->PlayerController;
    if (!PlayerController) return;

    APawn* AcknowledgedPawn = PlayerController->AcknowledgedPawn;
    if (!AcknowledgedPawn) return;
}