#include "pch.h"
#include <vector>
#include <random>
#include <math.h>

std::vector<ImVec2> circles_pos;
std::vector<ImVec2> circles_dir;
std::vector<int> circles_radius;
void DrawCircle(ImVec2 pos, int radius, ImColor color)
{
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	unsigned char* color_ptr = (unsigned char*)&color;
	draw_list->AddCircleFilled(pos, radius - 1, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], 75));
}
void DrawLine(ImVec2 pos1, ImVec2 pos2, ImU32 color, int radius)
{
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float distance = std::sqrt(
		std::pow(pos2.x - pos1.x, 2) + // std:: pow
		std::pow(pos2.y - pos1.y, 2)    // std:: pow
	);
	float alpha;
	if (distance <= 20.0f) {
		alpha = 255.0f;
	}
	else {
		alpha = (1.0f - ((distance - 20.0f) / 25.0f)) * 255.0f;
	}

	int r = (color & 0xFF0000) >> 16; // Extract red component
	int g = (color & 0x00FF00) >> 8;  // Extract green component
	int b = (color & 0x0000FF);       // Extract blue component

	unsigned char* color_ptr = (unsigned char*)&color;

	draw_list->AddLine(pos1, pos2, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], static_cast<int>(alpha)), 1.0f);
	if (distance >= 40.0f) {
		draw_list->AddCircleFilled(pos1, radius - 0.96f, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], alpha * 200.0f));
		draw_list->AddCircleFilled(pos2, radius - 0.96f, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], alpha * 200.0f));
	}
	else if (distance <= 20.0f) {
		draw_list->AddCircleFilled(pos1, radius, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], alpha * 200.0f));
		draw_list->AddCircleFilled(pos2, radius, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], alpha * 200.0f));
	}
	else {
		float radius_factor = 1.0f - ((distance - 20.0f) / 20.0f);
		float offset_factor = 1.0f - radius_factor;
		float offset = (radius - radius * radius_factor) * offset_factor;
		draw_list->AddCircleFilled(pos1, radius - offset, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], alpha * 200.0f));
		draw_list->AddCircleFilled(pos2, radius - offset, IM_COL32(color_ptr[0], color_ptr[1], color_ptr[2], alpha * 200.0f));
	}
}
void MoveCircles()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 360);
	int P_ResX = GetSystemMetrics(SM_CXSCREEN);
	int P_ResY = GetSystemMetrics(SM_CYSCREEN);
	float myFloatX = static_cast<float>(P_ResX);
	float myFloatY = static_cast<float>(P_ResY);
	for (int i = 0; i < circles_pos.size(); i++)
	{
		ImVec2& pos = circles_pos[i];
		ImVec2& dir = circles_dir[i];
		int radius = circles_radius[i];

		pos.x += dir.x * 0.6;
		pos.y += dir.y * 0.6;
		/*
		pos.x += dir.x * 0.4;
		pos.y += dir.y * 0.4;
		*/

		if (pos.x - radius < 0 || pos.x + radius > myFloatX)
		{
			dir.x = -dir.x;
			dir.y = dis(gen) % 2 == 0 ? -1 : 1;
		}

		if (pos.y - radius < 0 || pos.y + radius > myFloatY)
		{
			dir.y = -dir.y;
			dir.x = dis(gen) % 2 == 0 ? -1 : 1;
		}
	}
}
void DrawConstellation(ImColor color)
{
	MoveCircles();

	for (int i = 0; i < circles_pos.size(); i++)
	{
		DrawCircle(circles_pos[i], circles_radius[i], color);

		for (int j = i + 1; j < circles_pos.size(); j++)
		{
			float distance = ImGui::GetIO().FontGlobalScale * std::sqrt(
				std::pow(circles_pos[j].x - circles_pos[i].x, 2) + // std:: pow
				std::pow(circles_pos[j].y - circles_pos[i].y, 2)    // std:: pow
			);

			if (distance <= 45.0f)
			{
				DrawLine(circles_pos[i], circles_pos[j], color, circles_radius[i]);
			}
		}
	}
}
void SetupCircles()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);
	std::uniform_int_distribution<> pos_dis(0, static_cast<int>(2560));
	std::uniform_int_distribution<> pos_dis_y(0, static_cast<int>(1440));

	for (int i = 0; i < 500; i++) // 1000 is the number of cricle you render i recommend 400.
	{
		circles_pos.push_back(ImVec2(pos_dis(gen), pos_dis_y(gen)));
		circles_dir.push_back(ImVec2(dis(gen) == 0 ? -1 : 1, dis(gen) == 0 ? -1 : 1));
		circles_radius.push_back(3);
	}
}