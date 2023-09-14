#include "pch.h"

inline void RenderCollapsingList(ImVec2 ScreenStartPosition, ImColor Color, std::vector<std::string> DisplayArray, float HeightFactor)
{
	auto StartPosition = *reinterpret_cast<const ImVec2*>(&ScreenStartPosition);
	for (size_t s = 0; s < DisplayArray.size(); s++)
	{
		auto& DisplayString = DisplayArray[s];
		if (DisplayString.length() < 1) continue;
		auto CurrentPosition = ImVec2(StartPosition.x, StartPosition.y);
		auto StringSize = ImGui::CalcTextSize(DisplayString.c_str());
		CurrentPosition.y += StringSize.y;
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(CurrentPosition.x, StartPosition.y), Color, DisplayString.c_str(), DisplayString.c_str() + strlen(DisplayString.c_str()), 500);
		StartPosition.y += HeightFactor;
	}
}

void RenderLine(FVector2D start, FVector2D end, ImColor color, float size)
{
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.X, start.Y), ImVec2(end.X, end.Y), color, size);
}

void RenderText(FVector2D pos, ImColor color, const char* string)
{
	ImGui::GetBackgroundDrawList()->AddText(nullptr, 16, ImVec2(pos.X, pos.Y), color, string);
}

void RenderVerticalText(FVector2D pos, ImColor color, const char* string)
{
	float offsetY = 0.0f;
	float lineHeight = 16.0f;  // Assuming 16 as the height of each character. Adjust if needed.

	while (*string)
	{
		char currentChar[2] = { *string, '\0' };  // Extract current character as a string.
		ImGui::GetBackgroundDrawList()->AddText(nullptr, 16, ImVec2(pos.X, pos.Y + offsetY), color, currentChar);
		offsetY += lineHeight;
		string++;
	}
}

void RenderRect(const FVector initial_pos, float w, float h, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(initial_pos.X, initial_pos.Y), ImVec2(initial_pos.X + w, initial_pos.Y + h), color);
}

void RenderFilledRect(const FVector initial_pos, float w, float h, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(initial_pos.X, initial_pos.Y), ImVec2(initial_pos.X + w, initial_pos.Y + h), color);
}

void RenderCirc(ImVec2 center, float radius, ImColor color, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(center.x, center.y), radius, color, ImGui::GetBackgroundDrawList()->_CalcCircleAutoSegmentCount(radius), thickness);
}

void RenderFilledCirc(ImVec2 center, float radius, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(center.x, center.y), radius, color, ImGui::GetBackgroundDrawList()->_CalcCircleAutoSegmentCount(radius));
}

void RenderCornerBox(float x, float y, float w, float h, float thick, ImColor color)
{
	RenderLine(FVector2D(x, y), FVector2D(x + w / 4.f, y), color, thick);
	RenderLine(FVector2D(x, y), FVector2D(x, y + h / 4.f), color, thick);

	RenderLine(FVector2D(x + w, y), FVector2D(x + w - w / 4.f, y), color, thick);
	RenderLine(FVector2D(x + w, y), FVector2D(x + w, y + h / 4.f), color, thick);

	RenderLine(FVector2D(x, y + h), FVector2D(x + w / 4.f, y + h), color, thick);
	RenderLine(FVector2D(x, y + h), FVector2D(x, y + h - h / 4.f), color, thick);

	RenderLine(FVector2D(x + w, y + h), FVector2D(x + w, y + h - h / 4.f), color, thick);
	RenderLine(FVector2D(x + w, y + h), FVector2D(x + w - w / 4.f, y + h), color, thick);
}

void RenderRectWindow(const FVector initial_pos, float w, float h, ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(initial_pos.X, initial_pos.Y), ImVec2(initial_pos.X + w, initial_pos.Y + h), color);
}

void RenderFilledRectWindow(const FVector initial_pos, float w, float h, ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(initial_pos.X, initial_pos.Y), ImVec2(initial_pos.X + w, initial_pos.Y + h), color);
}

void RenderLineWindow(FVector2D start, FVector2D end, ImColor color, float size)
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(start.X, start.Y), ImVec2(end.X, end.Y), color, size);
}

void RenderRadar()
{
	RenderFilledRectWindow({ RadarX, RadarY, 0.0f }, RadarSize, RadarSize, { 21, 20, 27 });
	RenderRectWindow({ RadarX, RadarY, 0.0f }, RadarSize + 1, RadarSize + 1, { 0.43f, 0.43f, 0.50f, 0.50f });
}
