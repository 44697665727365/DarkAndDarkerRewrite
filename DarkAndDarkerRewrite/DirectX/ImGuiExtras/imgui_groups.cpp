#include "pch.h"
#include "imgui_groups.h"
#include "imgui_addons.h"
#include "IconsFontAwesome6.h"

CImGrp* ImGrp;


void CImGrp::CheckboxPopup(const char* label, const char* popup, bool* v)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    static ImGuiCol FocText = ImGuiCol_TextDisabled;
    
    ImGui::TextUnformatted(label);

    ImGui::SameLine(ImGui::GetWindowSize().x - ImGui::CalcTextSize(ICON_FA_ELLIPSIS).x - style.WindowPadding.x - (style.FramePadding.x * 2) - ImGui::GetFontSize());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, style.ItemSpacing.y));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(FocText));
    if (ImGui::SmallButton(ICON_FA_ELLIPSIS))
    {
        ImGui::OpenPopup(popup);
    }
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar();
    if (ImGui::IsItemHovered())
        FocText = ImGuiCol_Text;
    else
        FocText = ImGuiCol_TextDisabled;

    ImGui::SameLine();
    std::string str1 = "##";
    std::string str2 = label;
    ImAdd->CheckboxW((str1 + str2).c_str(), v);
    ImGui::PopStyleVar();
}

void CImGrp::CheckboxSliderInt(const char* label, bool* bv, int* fv, int v_min, int v_max, const char* format, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = label;
    std::string str3 = "checkbox";

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.ItemSpacing.x - ImGui::GetFontSize() - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    ImGui::PushItemWidth(width);
    ImGui::SliderInt((str1 + str2).c_str(), fv, v_min, v_max, format);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImAdd->CheckboxW((str1 + str2 + str3).c_str(), bv);
}

void CImGrp::CheckboxSliderFloat(const char* label, bool* bv, float* fv, float v_min, float v_max, const char* format, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = label;
    std::string str3 = "checkbox";

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.ItemSpacing.x - ImGui::GetFontSize() - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    ImGui::PushItemWidth(width);
    ImGui::SliderFloat((str1 + str2).c_str(), fv, v_min, v_max, format);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImAdd->CheckboxW((str1 + str2 + str3).c_str(), bv);
}

void CImGrp::CheckboxDragInt(const char* label, bool* bv, int* fv, int v_speed, int v_min, int v_max, const char* format, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = label;
    std::string str3 = "checkbox";

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.ItemSpacing.x - ImGui::GetFontSize() - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    ImGui::PushItemWidth(width);
    ImGui::DragInt((str1 + str2).c_str(), fv, v_speed, v_min, v_max, format);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImAdd->CheckboxW((str1 + str2 + str3).c_str(), bv);
}

void CImGrp::CheckboxDragFloat(const char* label, bool* bv, float* fv, float v_speed, float v_min, float v_max, const char* format, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = label;
    std::string str3 = "checkbox";

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.ItemSpacing.x - ImGui::GetFontSize() - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    ImGui::PushItemWidth(width);
    ImGui::DragFloat((str1 + str2).c_str(), fv, v_speed, v_min, v_max, format);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImAdd->CheckboxW((str1 + str2 + str3).c_str(), bv);
}

void CImGrp::CheckboxCombo(const char* text, bool* v, int* current_item, const char* items_separated_by_zeros, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = text;
    std::string str3 = "checkbox";

    ImGui::TextUnformatted(text);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.ItemSpacing.x - ImGui::GetFontSize() - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 0));
    ImGui::PushItemWidth(width);
    ImGui::Combo((str1 + str2).c_str(), current_item, items_separated_by_zeros);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImAdd->CheckboxW((str1 + str2 + str3).c_str(), v);
}