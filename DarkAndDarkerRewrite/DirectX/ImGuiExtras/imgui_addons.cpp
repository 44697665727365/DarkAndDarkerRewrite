#include "pch.h"
#include "imgui_addons.h"

CImAdd* ImAdd;

void CImAdd::TextSide(const char* text1, const char* text2)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::Text(text1);
    ImGui::SameLine(ImGui::GetWindowSize().x - ImGui::CalcTextSize(text2).x - style.WindowPadding.x);
    ImGui::TextDisabled(text2);
}

void CImAdd::Tooltip(const char* szText)
{
    if (strlen(szText) && ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(szText);
        ImGui::EndTooltip();
    }
}

void CImAdd::HotKeyEx(int* k, const ImVec2& size_arg)
{
    static const char* keyname = KeyNames[*k];
    static bool ispressed = false;
    if (ImGui::Button(keyname, size_arg))
    {
        keyname = "...";
        ispressed = true;
    }
    if (ispressed)
    {
        bool ignore_key = false;
        for (auto ignored_key : IgnoredKeys) {
            if (GetAsyncKeyState(ignored_key) & 0x8000) {
                ignore_key = true;
                break;
            }
        }
        if (!ignore_key) {
            for (auto& Key : KeyCodes)
            {
                if (GetAsyncKeyState(Key) & 0x8000) {
                    *k = Key;
                    ispressed = false;
                }
            }
        }
    }
    else
    {
        keyname = KeyNames[*k];
    }
}

void CImAdd::HotKey(const char* label, int* k, int width, int pad)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::BeginGroup();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(pad, pad));
    ImGui::Spacing();
    ImGui::PopStyleVar();

    ImGui::TextUnformatted(label);
    ImGui::EndGroup();

    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(pad, pad));
    this->HotKeyEx(k, ImVec2(width, ImGui::GetFontSize() + pad * 2));
    ImGui::PopStyleVar();
}

ImVec4 CImAdd::Hex2RGBA(int hexValue, float alpha)
{
    float r = (hexValue >> 16) & 0xFF;
    float g = (hexValue >> 8) & 0xFF;
    float b = hexValue & 0xFF;

    return ImVec4(r / 255, g / 255, b / 255, alpha);
}

void CImAdd::SeparatorText(const char* text)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    auto pos = ImGui::GetCursorScreenPos();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.62f, 0.62f, 0.63f, 1.00f));
    ImGui::Text(text);
    ImGui::PopStyleColor();
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + ImGui::CalcTextSize(text).x + style.WindowPadding.x, pos.y + ImGui::CalcTextSize(text).y / 2), ImVec2(pos.x + ImGui::GetWindowSize().x - style.WindowPadding.x * 2, pos.y + ImGui::CalcTextSize(text).y / 2), ImGui::GetColorU32(ImGuiCol_Border));
}

bool CImAdd::ToggleButtonEx(const char* label, bool* v)
{
    using namespace ImGui;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    //float height = ImGui::GetFrameHeight( );
    float height = ImGui::GetFontSize();
    const ImVec2 pos = window->DC.CursorPos;

    float width = height * 2.f;
    float radius = height * 0.50f;

    const ImRect total_bb(pos, ImVec2(pos.x + width + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), pos.y + label_size.y /*+ style.FramePadding.y * 2.0f*/));

    ItemSize(total_bb/*, style.FramePadding.y*/);
    if (!ItemAdd(total_bb, id))
        return false;

    float last_active_id_timer = g.LastActiveIdTimer;

    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *v = !(*v);
        MarkItemEdited(id);
        g.LastActiveIdTimer = 0.f;
    }

    if (g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed)
        g.LastActiveIdTimer = last_active_id_timer;

    float t = *v ? 1.0f : 0.0f;

    if (g.LastActiveId == id)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / 0.1f);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg = GetColorU32((held && hovered) ? *v ? ImGuiCol_SliderGrabActive : ImGuiCol_FrameBgActive : hovered ? *v ? ImGuiCol_SliderGrabActive : ImGuiCol_FrameBgHovered : *v ? ImGuiCol_SliderGrab : ImGuiCol_FrameBg);

    const ImRect frame_bb(pos, ImVec2(pos.x + width, pos.y + height));

    RenderFrame(frame_bb.Min, frame_bb.Max, col_bg, false, height * 0.5f);
    RenderNavHighlight(total_bb, id);

    ImVec2 label_pos = ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y /*+ style.FramePadding.y*/);
    RenderText(label_pos, label);
    window->DrawList->AddCircleFilled(ImVec2(pos.x + radius + t * (width - radius * 2.0f), pos.y + radius), radius /*- style.FramePadding.x*/, ImGui::GetColorU32(*v ? ImGuiCol_CheckMark : ImGuiCol_TextDisabled), 36);

    return pressed;
}

bool CImAdd::ToggleButton(const char* label, bool* v)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - style.WindowPadding.x - ImGui::GetFontSize() * 2);
    std::string str1 = "##";
    std::string str2 = label;
    return this->ToggleButtonEx((str1 + str2).c_str(), v);
}

struct button_state {

    ImVec4 background_color;

};

bool CImAdd::AnimButton(const char* label, const ImVec2& size_arg, float speed, ImGuiButtonFlags flags, ImDrawFlags drawflag)
{
    using namespace ImGui;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    static std::map<ImGuiID, button_state> anim;
    auto it_anim = anim.find(id);

    if (it_anim == anim.end())
    {
        anim.insert({ id, button_state() });
        it_anim = anim.find(id);
    }

    it_anim->second.background_color = ImLerp(it_anim->second.background_color, IsItemActive() ? ImColor(GetColorU32(ImGuiCol_ButtonActive)) : hovered ? ImColor(GetColorU32(ImGuiCol_ButtonHovered)) : ImColor(GetColorU32(ImGuiCol_Button)), g.IO.DeltaTime * speed);

    window->DrawList->AddRectFilled(bb.Min, bb.Max, GetColorU32(it_anim->second.background_color), style.FrameRounding, drawflag);
    if (style.FrameBorderSize > 0.0f)
        window->DrawList->AddRect(bb.Min, bb.Max, GetColorU32(ImGuiCol_Border), style.FrameRounding, drawflag, style.FrameBorderSize);

    RenderTextClipped({ bb.Min.x + style.FramePadding.x , bb.Min.y + style.FramePadding.y }, { bb.Max.x - style.FramePadding.x , bb.Max.y - style.FramePadding.y }, label, NULL, &label_size, style.ButtonTextAlign, &bb);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return pressed;
}

void CImAdd::NavigationRadio(const char* text, ImVec2 size, int id, int* t_ids, int speed)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGuiCol FocText = ImGuiCol_Text;
    ImGuiCol ActText = ImGuiCol_SliderGrab;

    auto pos = ImGui::GetCursorScreenPos();

    if (id == *t_ids)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4());
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
        AnimButton(text, size, speed, 0);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);
        FocText = ImGuiCol_Text;
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4());
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
        bool pressed = AnimButton(text, size, speed, 0);
        if (pressed)
        {
            *t_ids = id;
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);

        if (ImGui::IsItemHovered())
            FocText = ImGuiCol_Text;
        else
            FocText = ImGuiCol_TextDisabled;
    }

    // Animate the text color
    static std::map<int, ImVec4> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, ImVec4() });
        it_anim = anim.find(id);
    }
    it_anim->second = ImLerp(it_anim->second, ImColor(ImGui::GetStyleColorVec4(FocText)), g.IO.DeltaTime * speed);

    int border_size = 1;
    ImGui::GetWindowDrawList()->AddText(g.Font, ImGui::GetFontSize(), pos + (ImVec2(size.y, size.y) / 2) - (ImGui::CalcTextSize(text) / 2), ImGui::ColorConvertFloat4ToU32(it_anim->second), text);
}


void CImAdd::NavigationRadioIcon(const char* text, ImVec2 size, int id, int* t_ids, int speed)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGuiCol FocText = ImGuiCol_Text;
    ImGuiCol ActText = ImGuiCol_Text;

    auto pos = ImGui::GetCursorScreenPos();

    if (id == *t_ids)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4());
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
        {
            AnimButton(text, size, speed, 0);
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);
        FocText = ImGuiCol_Text;
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4());
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
        if (AnimButton(text, size, speed, 0))
        {
            *t_ids = id;
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);
        if (ImGui::IsItemHovered())
            FocText = ImGuiCol_Text;
        else
            FocText = ImGuiCol_TextDisabled;
    }
    int border_size = 1;

    // Animate the text color
    static std::map<int, ImVec4> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, ImVec4() });
        it_anim = anim.find(id);
    }
    it_anim->second = ImLerp(it_anim->second, ImColor(ImGui::GetStyleColorVec4(FocText)), g.IO.DeltaTime * speed);

    ImGui::GetWindowDrawList()->AddText(g.Font, ImGui::GetFontSize(), pos + (ImVec2(size.y, size.y) / 2) - (ImGui::CalcTextSize(text) / 2), ImGui::GetColorU32(it_anim->second), text);
    if (id == *t_ids)
    {
        ImGui::GetWindowDrawList()->AddRectFilledMultiColor(pos + ImVec2(0, size.y - border_size), pos + ImVec2(size.x / 2, size.y), IM_COL32(0, 0, 0, 0), ImGui::GetColorU32(it_anim->second), ImGui::GetColorU32(it_anim->second), IM_COL32(0, 0, 0, 0));
        ImGui::GetWindowDrawList()->AddRectFilledMultiColor(pos + ImVec2(size.x / 2, size.y - border_size), pos + ImVec2(size.x, size.y), ImGui::GetColorU32(it_anim->second), IM_COL32(0, 0, 0, 0), IM_COL32(0, 0, 0, 0), ImGui::GetColorU32(it_anim->second));
    }
}


bool CImAdd::SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, float grab_radius, ImGuiSliderFlags flags)
{
    using namespace ImGui;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const float w = GetWindowSize().x - style.WindowPadding.x * 2;

    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    const ImRect frame_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y), ImVec2(w + window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y * 2));
    const ImRect total_bb(frame_bb.Min, ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x + frame_bb.Max.x : frame_bb.Max.x, frame_bb.Max.y + label_size.y));

    const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
        return false;

    // Default format string when passing NULL
    if (format == NULL)
        format = DataTypeGetInfo(data_type)->PrintFmt;

    const bool hovered = ItemHoverable(frame_bb, id);
    const bool clicked = hovered && IsMouseClicked(0, id);
    const bool make_active = (clicked || g.NavActivateId == id || g.NavActivateInputId == id);

    if (make_active)
    {
        SetActiveID(id, window);
        SetFocusID(id, window);
        FocusWindow(window);
        g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
    }

    // Draw frame
    const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
    RenderNavHighlight(frame_bb, id);
    RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

    // Slider behavior
    ImRect grab_bb;
    const bool value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
    if (value_changed)
        MarkItemEdited(id);

    // Render grab
    if (grab_bb.Max.x > grab_bb.Min.x)
        //window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);
        window->DrawList->AddRectFilled(frame_bb.Min + ImVec2(2, 2), grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

    // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
    char value_buf[64];
    const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
    if (g.LogEnabled)
        LogSetNextTextDecoration("{", "}");
    PushStyleColor(ImGuiCol_Text, GetStyleColorVec4(ImGuiCol_TextDisabled));
    RenderTextClipped(ImVec2(frame_bb.Min.x, frame_bb.Min.y - style.ItemInnerSpacing.x - label_size.y * 2), frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(1.0f, 0.5f));
    ImGui::PopStyleColor();

    if (label_size.x > 0.0f)
        RenderText(ImVec2(frame_bb.Min.x/* + style.ItemInnerSpacing.x*/, frame_bb.Min.y - label_size.y - style.FramePadding.y), label);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return value_changed;
}

bool CImAdd::SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
    return this->SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, 6, flags);
}

bool CImAdd::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    return this->SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, 6, flags);
}

bool CImAdd::SliderIntW(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    ImGui::PushItemWidth(width);
    bool clicked = ImGui::SliderInt(label, v, v_min, v_max, format, flags);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    return clicked;
}

bool CImAdd::SliderFloatW(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags, int width)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - width - style.WindowPadding.x);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    ImGui::PushItemWidth(width);
    bool clicked = ImGui::SliderFloat(label, v, v_min, v_max, format, flags);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    return clicked;
}

struct checkbox_state {

    ImVec4 background_color;

};

bool CImAdd::CheckboxEx(const char* label, bool* v, float speed)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    const float square_sz = ImGui::GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id))
    {
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return false;
    }

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *v = !(*v);
        ImGui::MarkItemEdited(id);
    }

    static std::map<ImGuiID, checkbox_state> anim;
    auto it_anim = anim.find(id);

    if (it_anim == anim.end())
    {
        anim.insert({ id, checkbox_state() });
        it_anim = anim.find(id);
    }

    it_anim->second.background_color = ImLerp(it_anim->second.background_color, *v ? ImColor(ImGui::GetColorU32(ImGuiCol_SliderGrab)) : (held && hovered) ? ImColor(ImGui::GetColorU32(ImGuiCol_FrameBgActive)) : hovered ? ImColor(ImGui::GetColorU32(ImGuiCol_FrameBgHovered)) : ImColor(ImGui::GetColorU32(ImGuiCol_FrameBg)), g.IO.DeltaTime * speed);

    const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
    ImGui::RenderNavHighlight(total_bb, id);
    window->DrawList->AddRectFilled(check_bb.Min, check_bb.Max, ImGui::GetColorU32(it_anim->second.background_color), style.FrameRounding);
    if (!*v)
    {
        window->DrawList->AddRect(check_bb.Min, check_bb.Max, ImGui::GetColorU32(ImGuiCol_Border), style.FrameRounding);
    }

    ImU32 check_col = ImGui::GetColorU32(ImGuiCol_CheckMark);
    bool mixed_value = (g.LastItemData.InFlags & ImGuiItemFlags_MixedValue) != 0;
    if (mixed_value)
    {
        // Undocumented tristate/mixed/indeterminate checkbox (#2644)
        // This may seem awkwardly designed because the aim is to make ImGuiItemFlags_MixedValue supported by all widgets (not just checkbox)
        ImVec2 pad(ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)), ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)));
        window->DrawList->AddRectFilled(check_bb.Min + pad, check_bb.Max - pad, check_col, style.FrameRounding);
    }
    else if (*v)
    {
        const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
        ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(pad, pad), check_col, square_sz - pad * 2.0f);
    }

    ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
    if (g.LogEnabled)
        ImGui::LogRenderedText(&label_pos, mixed_value ? "[~]" : *v ? "[x]" : "[ ]");
    if (label_size.x > 0.0f)
    {
        ImGui::RenderText(label_pos, label);
    }

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
    return pressed;
}

bool CImAdd::CheckboxW(const char* label, bool* v, float speed)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    bool pressed = this->CheckboxEx(label, v);
    ImGui::PopStyleVar();
    return pressed;
}

bool CImAdd::Checkbox(const char* label, bool* v)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
    //ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(*v ? ImGuiCol_Text : ImGuiCol_TextDisabled));
    ImGui::TextUnformatted(label);
    //ImGui::PopStyleColor();
    if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        *v = !*v;
    ImGui::SameLine(ImGui::GetWindowSize().x - ImGui::GetFontSize() - style.WindowPadding.x);
    std::string str1 = "##";
    std::string str2 = label;
    bool pressed = this->CheckboxEx((str1 + str2).c_str(), v);
    ImGui::PopStyleVar();
    return pressed;
}

bool CImAdd::ColorEdit4Ex(const char* label, float col[4])
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = label;

    if (ImGui::ColorButton((str1 + str2).c_str(), ImVec4(col[0], col[1], col[2], col[3]), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview, { ImGui::GetFontSize() * 2, ImGui::GetFontSize() }))
    {
        ImGui::OpenPopup(("COLORPICKER##" + str2).c_str());
    }
    if (ImGui::BeginPopup(("COLORPICKER##" + str2).c_str()))
    {
        {
            ImGui::ColorPicker4(label, col, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
        }
        ImGui::EndPopup();
    }
}

bool CImAdd::ColorEdit4(const char* label, float col[4])
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::TextUnformatted(label);
    ImGui::SameLine(ImGui::GetWindowSize().x - style.WindowPadding.x - ImGui::GetFontSize() * 2);
    return this->ColorEdit4Ex(label, col);
}

void CImAdd::ComboEx(const char* label, int* current_item, const char* items_separated_by_zeros)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_FrameBgActive));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
    //ImGui::PushItemWidth(ImGui::GetWindowSize().x - style.WindowPadding.x * 2);
    ImGui::Combo(label, current_item, items_separated_by_zeros);
    //ImGui::PopItemWidth();
    ImGui::PopStyleColor(3);
}

void CImAdd::Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int width, int pad)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    std::string str1 = "##";
    std::string str2 = label;

    ImGui::BeginGroup();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(pad, pad));
    ImGui::Spacing();
    ImGui::PopStyleVar();
    ImGui::TextUnformatted(label);
    ImGui::EndGroup();

    ImGui::SameLine(ImGui::GetWindowSize().x - style.WindowPadding.x - width);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(pad, pad));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(pad, pad));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(pad, pad));
    ImGui::PushItemWidth(width);
    this->ComboEx((str1 + str2).c_str(), current_item, items_separated_by_zeros);
    ImGui::PopItemWidth();
    ImGui::PopStyleVar(3);
}