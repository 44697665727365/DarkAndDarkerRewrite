#pragma once
#include "pch.h"

inline void RenderCollapsingList(ImVec2 ScreenStartPosition, ImColor Color, std::vector<std::string> DisplayArray, float HeightFactor);
void RenderLine(FVector2D start, FVector2D end, ImColor color, float size);
void RenderText(FVector2D pos, ImColor color, const char* string);
void RenderVerticalText(FVector2D pos, ImColor color, const char* string);
void RenderRect(const FVector initial_pos, float w, float h, ImColor color);
void RenderFilledRect(const FVector initial_pos, float w, float h, ImColor color);
void RenderCirc(ImVec2 center, float radius, ImColor color, float thickness);
void RenderFilledCirc(ImVec2 center, float radius, ImColor color);
void RenderCornerBox(float x, float y, float w, float h, float thick, ImColor color);
void RenderRadar();