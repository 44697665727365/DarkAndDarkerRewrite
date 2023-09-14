#pragma once

//ViewPoint (FOV)
typedef void(*GetViewPoint_t)(ULocalPlayer* _this, FMinimalViewInfo* OutViewInfo);
extern GetViewPoint_t GetViewPoint;
void GetViewPoint_f(ULocalPlayer* _this, FMinimalViewInfo* OutViewInfo);