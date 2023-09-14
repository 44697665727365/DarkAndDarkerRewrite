#pragma once
#include "pch.h"

void DrawCircle(ImVec2 pos, int radius, ImColor color);
void DrawLine(ImVec2 pos1, ImVec2 pos2, ImU32 color, int radius);
void MoveCircles();
void DrawConstellation(ImColor color);
void SetupCircles();