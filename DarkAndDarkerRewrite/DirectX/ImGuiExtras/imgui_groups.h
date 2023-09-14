#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "DirectX/ImGui/imgui.h"
#include "DirectX/ImGui/imgui_impl_dx12.h"
#include "DirectX/ImGui/imgui_impl_win32.h"
#include "DirectX/ImGui/imgui_internal.h"

class CImGrp
{
public:
    CImGrp();

    IMGUI_API void          CheckboxPopup(const char* label, const char* popup, bool* v);
    IMGUI_API void          CheckboxSliderInt(const char* label, bool* bv, int* fv, int v_min, int v_max, const char* format = "%d", int width = 70);
    IMGUI_API void          CheckboxSliderFloat(const char* label, bool* bv, float* fv, float v_min, float v_max, const char* format = "%.1f", int width = 70);
    IMGUI_API void          CheckboxDragInt(const char* label, bool* bv, int* fv, int v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", int width = 70);
    IMGUI_API void          CheckboxDragFloat(const char* label, bool* bv, float* fv, float v_speed = 1.0f, float v_min = 0, float v_max = 0, const char* format = "%.1f", int width = 70);
    IMGUI_API void          CheckboxCombo(const char* text, bool* v, int* current_item, const char* items_separated_by_zeros, int width = 70);
};

extern CImGrp* ImGrp;