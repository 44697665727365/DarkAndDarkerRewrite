#include "pch.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "DirectX/ImGui/imgui_internal.h"
#include "DirectX/ImGuiExtras/imgui_addons.h"
#include "DirectX/ImGuiExtras/IconsFontAwesome6.h"
#include "DirectX/ImGuiExtras/imgui_groups.h"

namespace Gui
{
    static ImVec2					Size = { 550 , 400 };
    int                             TitlebarSize = 50;
    int                             MenubarSize = 30;
    int                             FooterbarSize;
    int                             PageID = 0;
    int                             NavID = 0;
    int                             AimbotID = 0;
    int                             VisualsID = 0;
    int                             ExploitsID = 0;
    int                             SettingsID = 0;
}

char search_buf[128] = "";

ImVec4 WinBgCol = ImVec4(0, 0, 0, 1);

#define min2(x,y) ((x)<(y)?x:y)
#define wh(a) ImColor(1.f,1.f,1.f,a)

void FX(ImDrawList* d, ImVec2 a, ImVec2 b, ImVec2 sz, ImVec2, float t, ImDrawFlags draw_flag)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    static float fl;
    if ((rand() % 500) == 0) fl = t;
    if ((t - fl) > 0)
    {
        auto ft = 0.25f;
        d->AddRectFilled(a, b, wh((ft - (t - fl)) / ft), 0, draw_flag);
    }

    for (int i = 0; i < 2000; ++i) {
        unsigned h = ImGui::GetID(d + i + int(t / 4));
        auto f = fmodf(t + fmodf(h / 777.f, 99), 99);
        auto tx = h % (int)sz.x;
        auto ty = h % (int)sz.y;
        if (f < 1) {
            auto py = ty - 1000 * (1 - f);
            d->AddLine({ a.x + tx, a.y + py }, { a.x + tx, a.y + min2(py + 10,ty) }, (ImU32)-1);
        }
        else if (f < 1.2f)
            d->AddCircle({ a.x + tx, a.y + ty }, (f - 1) * 10 + h % 5, wh(1 - (f - 1) * 5.f));
    }
}

void RenderGUI()
{
    ImGuiStyle& style = ImGui::GetStyle();

    Gui::FooterbarSize = ImGui::GetFrameHeight();

    ImGuiWindowFlags main_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    ImGui::SetNextWindowPos({ (GetSystemMetrics(SM_CXSCREEN) / 2) - (Gui::Size.x / 2) , (GetSystemMetrics(SM_CYSCREEN) / 2) - (Gui::Size.y / 2) }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(Gui::Size);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(Xors("Window::WindowName"), nullptr, main_window_flags); {
    ImGui::PopStyleVar();
        FX(ImGui::GetBackgroundDrawList(), ImVec2(0, 0), ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImGui::GetTime(), ImDrawFlags_RoundCornersBottomRight);

        ImGui::GetBackgroundDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImVec2(ImGui::GetWindowSize().x, Gui::TitlebarSize), ImGui::GetColorU32(ImGuiCol_WindowBg), style.WindowRounding, ImDrawFlags_RoundCornersTop); // Titlebar
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(0, Gui::TitlebarSize + style.WindowBorderSize), ImGui::GetWindowPos() + ImVec2(ImGui::GetWindowSize().x, Gui::TitlebarSize + Gui::MenubarSize + style.WindowBorderSize), ImGui::GetColorU32(ImGuiCol_ChildBg), style.WindowRounding, ImDrawFlags_RoundCornersNone); // Menubar
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(0, Gui::TitlebarSize + Gui::MenubarSize + style.WindowBorderSize * 2), ImGui::GetWindowPos() + ImGui::GetWindowSize() - ImVec2(0, Gui::FooterbarSize + style.WindowBorderSize), ImGui::GetColorU32(ImGuiCol_WindowBg), style.WindowRounding, ImDrawFlags_RoundCornersNone); // Main
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(0, ImGui::GetWindowSize().y - Gui::FooterbarSize), ImGui::GetWindowPos() + ImGui::GetWindowSize(), ImGui::GetColorU32(ImGuiCol_ChildBg), style.WindowRounding, ImDrawFlags_RoundCornersBottom); // FooterBg
        if (style.WindowBorderSize >= 0.5)
        {
            ImGui::GetBackgroundDrawList()->AddRect(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImGui::GetWindowSize(), ImGui::GetColorU32(ImGuiCol_Border), style.WindowRounding);
            ImGui::GetBackgroundDrawList()->AddLine(ImGui::GetWindowPos() + ImVec2(style.WindowBorderSize, Gui::TitlebarSize), ImGui::GetWindowPos() + ImVec2(ImGui::GetWindowSize().x - style.WindowBorderSize, Gui::TitlebarSize), ImGui::GetColorU32(ImGuiCol_Border), style.WindowBorderSize); // Border 1
            ImGui::GetBackgroundDrawList()->AddLine(ImGui::GetWindowPos() + ImVec2(style.WindowBorderSize, Gui::TitlebarSize + Gui::MenubarSize + style.WindowBorderSize), ImGui::GetWindowPos() + ImVec2(ImGui::GetWindowSize().x - style.WindowBorderSize, Gui::TitlebarSize + Gui::MenubarSize + style.WindowBorderSize), ImGui::GetColorU32(ImGuiCol_Border), style.WindowBorderSize); // Border 2
            ImGui::GetBackgroundDrawList()->AddLine(ImGui::GetWindowPos() + ImVec2(style.WindowBorderSize, ImGui::GetWindowSize().y - Gui::FooterbarSize - style.WindowBorderSize), ImGui::GetWindowPos() + ImVec2(ImGui::GetWindowSize().x - style.WindowBorderSize, ImGui::GetWindowSize().y - Gui::FooterbarSize - style.WindowBorderSize), ImGui::GetColorU32(ImGuiCol_Border), style.WindowBorderSize); // Border 3
        }
        ImGui::BeginChild(Xors("Titlebar"), ImVec2(0, Gui::TitlebarSize + style.WindowBorderSize), false, ImGuiWindowFlags_NoBackground);
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2());
            auto NavBtnsSize = ImVec2(ImGui::GetWindowSize().y, ImGui::GetWindowSize().y);
            {
                ImAdd->NavigationRadioIcon(Xors("Aimbot"), NavBtnsSize, 0, &Gui::PageID);
                ImGui::SameLine();
                ImAdd->NavigationRadioIcon(Xors("Visuals"), NavBtnsSize, 1, &Gui::PageID);
                ImGui::SameLine();
                ImAdd->NavigationRadioIcon(Xors("Exploits"), NavBtnsSize, 2, &Gui::PageID);
                ImGui::SameLine();
                ImAdd->NavigationRadioIcon(Xors("Settings"), NavBtnsSize, 3, &Gui::PageID);
            }
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::SetCursorPosY(Gui::TitlebarSize);
        ImGui::BeginChild(Xors("Menubar"), ImVec2(0, Gui::MenubarSize + style.WindowBorderSize * 2), false, ImGuiWindowFlags_NoBackground);
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2());
            {
                ImGui::SetCursorPos(style.WindowPadding);
                if (Gui::PageID == 0) {
                    ImGui::TextDisabled(Xors("Aimbot"));
                    auto NavListSize = ImVec2(60, ImGui::GetWindowSize().y);
                    ImGui::SetCursorPosY(NULL);
                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x + style.WindowPadding.x - NavListSize.x * 2);
                    ImGui::BeginGroup(); {
                        ImAdd->NavigationRadio(Xors("Players"), NavListSize, 0, &Gui::AimbotID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Monsters"), NavListSize, 1, &Gui::AimbotID);
                    }
                    ImGui::EndGroup();
                }
                else if (Gui::PageID == 1) {
                    ImGui::TextDisabled(Xors("Visuals"));
                    auto NavListSize = ImVec2(60, ImGui::GetWindowSize().y);
                    ImGui::SetCursorPosY(NULL);
                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x + style.WindowPadding.x - NavListSize.x * 6);
                    ImGui::BeginGroup(); {
                        ImAdd->NavigationRadio(Xors("Team"), NavListSize, 0, &Gui::VisualsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Enemy"), NavListSize, 1, &Gui::VisualsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Monsters"), NavListSize, 2, &Gui::VisualsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Loot"), NavListSize, 3, &Gui::VisualsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Radar"), NavListSize, 4, &Gui::VisualsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Misc"), NavListSize, 5, &Gui::VisualsID);
                    }
                    ImGui::EndGroup();
                }
                else if (Gui::PageID == 2) {
                    ImGui::TextDisabled(Xors("Exploits"));
                    auto NavListSize = ImVec2(60, ImGui::GetWindowSize().y);
                    ImGui::SetCursorPosY(NULL);
                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x + style.WindowPadding.x - NavListSize.x * 3);
                    ImGui::BeginGroup(); {
                        ImAdd->NavigationRadio(Xors("Movement"), NavListSize, 0, &Gui::ExploitsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Visual"), NavListSize, 1, &Gui::ExploitsID);
                        ImGui::SameLine();
                        ImAdd->NavigationRadio(Xors("Weapon"), NavListSize, 2, &Gui::ExploitsID);
                    }
                    ImGui::EndGroup();
                }
                else if (Gui::PageID == 3) {
                    ImGui::TextDisabled("Settings");
                    auto NavListSize = ImVec2(60, ImGui::GetWindowSize().y);
                    ImGui::SetCursorPosY(NULL);
                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x + style.WindowPadding.x - NavListSize.x * 1);
                    ImGui::BeginGroup(); {
                        ImAdd->NavigationRadio(Xors("Config"), NavListSize, 0, &Gui::SettingsID);
                    }
                    ImGui::EndGroup();
                }
            }
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::SetCursorPosY(Gui::TitlebarSize + Gui::MenubarSize + style.WindowBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
        ImGui::BeginChild("content", ImVec2(0, ImGui::GetWindowSize().y - Gui::TitlebarSize - Gui::MenubarSize - Gui::FooterbarSize - style.WindowBorderSize), true, ImGuiWindowFlags_NoBackground);
        ImGui::PopStyleVar();
        {
            auto GroupsSize = ImVec2(((ImGui::GetWindowSize().x / 2) - (style.WindowPadding.x * (2 + 1)) / 2), 0);

            switch (Gui::PageID) {
            case 0: //Aimbot
                if (Gui::AimbotID == 0) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ToggleButton(Xors("Master"), &bAimbot);
                            ImAdd->Checkbox(Xors("Smoothing"), &bAimSmoothness);
                            ImAdd->SliderFloat(Xors("Smoothness"), &sAimSmoothness, 0, 100);
                            ImAdd->Checkbox(Xors("Random Smoothing"), &bAimSmoothRandom);
                            ImAdd->Checkbox(Xors("Target Teamates"), &bTargetTeamates);
                            ImAdd->Checkbox(Xors("Target Line"), &bDrawTargetLine); ImGui::SameLine(); ImAdd->ColorEdit4(Xors("TargetLineColor"), (float*)&cTargetLine);
                            ImAdd->Checkbox(Xors("Target Name"), &bDrawTargetName); ImGui::SameLine(); ImAdd->ColorEdit4(Xors("TargetNameColor"), (float*)&cTargetName);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->HotKey(Xors("Aim Key"), &iAimKey);
                            ImAdd->SliderFloat(Xors("FOV"), &sFOVSize, 1.0f, 1200.0f);
                            ImAdd->SliderFloat(Xors("Smoothing"), &sAimSmoothness, 1.0f, 100.0f);
                            ImAdd->Combo(Xors("Aim Type"), &iAimType, Xors("None\0Silent\0FOV\0FOV-Visible\0Visible"));
                            ImAdd->Combo(Xors("Aim Bone"), &iAimBone, Xors("None\0Head\0Neck\0Torso\0Left Hand\0Right Hand\0Pelvis\0Left Foot\0Right Foot"));
                        }
                    }
                    ImGui::EndChild();
                }
                else if (Gui::AimbotID == 1) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ToggleButton(Xors("Master"), &bAimbot);
                            ImAdd->Checkbox(Xors("Smoothing"), &bAimSmoothness);
                            ImAdd->Checkbox(Xors("Random Smoothing"), &bAimSmoothRandom);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->HotKey(Xors("Aim Key"), &iAimKey);
                            ImAdd->SliderFloat(Xors("FOV"), &sFOVSize, 1.0f, 1200.0f);
                            ImAdd->SliderFloat(Xors("Smoothing"), &sAimSmoothness, 1.0f, 100.0f);
                            ImAdd->Combo(Xors("Aim Type"), &iAimType, Xors("None\0Silent\0FOV\0FOV-Visible\0Visible"));
                            ImAdd->Combo(Xors("Aim Bone"), &iAimBone, Xors("None\0Head\0Neck\0Torso\0Left Hand\0Right Hand\0Pelvis\0Left Foot\0Right Foot"));
                        }
                    }
                    ImGui::EndChild();
                }
                break;
            case 1: //Visuals
                if (Gui::VisualsID == 0) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ToggleButton(Xors("Master"), &bEnableESP);
                            ImAdd->Checkbox(Xors("Name"), &bTeamNames);
                            ImAdd->Checkbox(Xors("Health"), &bTeamHealth);
                            ImAdd->Checkbox(Xors("Class"), &bTeamClass);
                            ImAdd->Checkbox(Xors("Weapon"), &bTeamWeapon);
                            ImAdd->Checkbox(Xors("Distance"), &bTeamDistance);
                            ImAdd->Checkbox(Xors("Snaplines"), &bTeamSnaplines);
                            ImAdd->Checkbox(Xors("Skeleton"), &bTeamSkeleton);
                            ImAdd->Checkbox(Xors("View Angles"), &bTeamViewAngle);
                            ImAdd->Checkbox(Xors("Boxs"), &bTeamBoxs);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ColorEdit4(Xors("Name"), (float*)&cTeamNames);
                            ImAdd->ColorEdit4(Xors("Health"), (float*)&cTeamHealth);
                            ImAdd->ColorEdit4(Xors("Class"), (float*)&cTeamClass);
                            ImAdd->ColorEdit4(Xors("Weapon"), (float*)&cTeamWeapon);
                            ImAdd->ColorEdit4(Xors("Distance"), (float*)&cTeamDistance);
                            ImAdd->ColorEdit4(Xors("Snaplines"), (float*)&cTeamSnaplines);
                            ImAdd->ColorEdit4(Xors("Skeleton"), (float*)&cTeamSkeleton);
                            ImAdd->ColorEdit4(Xors("View Angles"), (float*)&cTeamViewAngles);
                            ImAdd->ColorEdit4(Xors("Boxs"), (float*)&cTeamBoxs);
                            ImAdd->Combo(Xors("Box Type"), &iSelectedTeamBox, Xors("None\0/2D\0/2D-Filled\0Corners\0/3D"));
                        }
                    }
                    ImGui::EndChild();
                }
                else if (Gui::VisualsID == 1) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ToggleButton(Xors("Master"), &bEnableESP);
                            ImAdd->Checkbox(Xors("Name"), &bEnemyNames);
                            ImAdd->Checkbox(Xors("Health"), &bEnemyHealth);
                            ImAdd->Checkbox(Xors("Class"), &bEnemyClass);
                            ImAdd->Checkbox(Xors("Weapon"), &bEnemyWeapon);
                            ImAdd->Checkbox(Xors("Distance"), &bEnemyDistance);
                            ImAdd->Checkbox(Xors("Snaplines"), &bEnemySnaplines);
                            ImAdd->Checkbox(Xors("Skeleton"), &bEnemySkeleton);
                            ImAdd->Checkbox(Xors("View Angles"), &bEnemyViewAngle);
                            ImAdd->Checkbox(Xors("Boxs"), &bEnemyBoxs);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ColorEdit4(Xors("Name"), (float*)&cEnemyNames);
                            ImAdd->ColorEdit4(Xors("Health"), (float*)&cEnemyHealth);
                            ImAdd->ColorEdit4(Xors("Class"), (float*)&cEnemyClass);
                            ImAdd->ColorEdit4(Xors("Weapon"), (float*)&cEnemyWeapon);
                            ImAdd->ColorEdit4(Xors("Distance"), (float*)&cEnemyDistance);
                            ImAdd->ColorEdit4(Xors("Snaplines"), (float*)&cEnemySnaplines);
                            ImAdd->ColorEdit4(Xors("Skeleton"), (float*)&cEnemySkeleton);
                            ImAdd->ColorEdit4(Xors("View Angles"), (float*)&cEnemyViewAngles);
                            ImAdd->ColorEdit4(Xors("Boxs"), (float*)&cEnemyBoxs);
                            ImAdd->Combo(Xors("Box Type"), &iSelectedEnemyBox, Xors("None\02D\02D Filled\0Corners\03D"));
                        }
                    }
                    ImGui::EndChild();
                }
                else if (Gui::VisualsID == 2) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ToggleButton(Xors("Master"), &bMonsters);
                            ImAdd->Checkbox(Xors("Health"), &bMonsterHealth);
                            ImAdd->Checkbox(Xors("Distance"), &bMonsterDistance);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ColorEdit4(Xors("Monsters"), (float*)&cMonsters);
                        }
                    }
                    ImGui::EndChild();
                }
                else if (Gui::VisualsID == 3) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->SeparatorText(Xors("Items"));
                            ImAdd->Checkbox(Xors("All Items"), &bRenderItems);
                            ImAdd->SeparatorText(Xors("Chests"));
                            ImAdd->Checkbox(Xors("Chests"), &bChests);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->SeparatorText(Xors("Items"));
                            ImAdd->SliderInt(Xors("Distance"), &iItemDistance, 0, 270);
                            ImAdd->SeparatorText(Xors("Chests"));
                            ImAdd->SliderInt(Xors("Distance"), &iDistanceCheckSlider, 0, 270);
                            ImAdd->ColorEdit4(Xors("Chests"), (float*)&cChests);
                        }
                    }
                    ImGui::EndChild();
                }
                else if (Gui::VisualsID == 4) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImGui::Checkbox(Xors("Radar"), &bRadar);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->SliderFloat(Xors("Radar X"), &RadarX, 0.0f, 500.f);
                            ImAdd->SliderFloat(Xors("Radar Y"), &RadarY, 0.0f, 500.0f);
                        }
                    }
                    ImGui::EndChild();
                }
                else if (Gui::VisualsID == 5) {
                    ImGui::BeginChild(Xors("groupToggles"), GroupsSize, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Toggleables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ToggleButton(Xors("Traps"), &bTraps);
                            ImAdd->Checkbox(Xors("Floor Portals"), &bFloorPortal);
                            ImAdd->Checkbox(Xors("Alter"), &bAlter);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild(Xors("groupAdjustables"), GroupsSize, true, ImGuiWindowFlags_MenuBar); {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(Xors("Adjustables")), ImGui::EndMenuBar();
                        {
                            ImAdd->ColorEdit4(Xors("Traps"), (float*)&cTraps);
                            ImAdd->ColorEdit4(Xors("Floor Portal"), (float*)&cFloorPortal);
                            ImAdd->ColorEdit4(Xors("Alter"), (float*)&cAlter);
                        }
                    }
                    ImGui::EndChild();
                    }
                break;
            case 2: //Exploits
                if (Gui::ExploitsID == 0) {

                }
                else if (Gui::ExploitsID == 1) {
                    ImAdd->Checkbox(Xors("Enable Features"), &bPlayerFeatures);
                    ImAdd->SliderFloat(Xors("Field of View"), &fFOV, 0.0f, 175.0f);
                    ImAdd->Checkbox(Xors("Free Cam"), &bFreeCam);
                    ImAdd->Tooltip(Xors("Use with Risk: Might be Detected!"));
                    ImAdd->Checkbox(Xors("Fullbright"), &bFullbright);
                    ImAdd->Checkbox(Xors("Player Stat List"), &bPlayerStatList);
                }
                else if (Gui::ExploitsID == 2) {

                }
                break;
            case 3: //Settings
                break;
            }
        }
        ImGui::EndChild();
        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - Gui::FooterbarSize - style.WindowBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, style.FramePadding);
        ImGui::BeginChild("footer", ImVec2(), true, ImGuiWindowFlags_NoBackground);
        ImGui::PopStyleVar();
        {
            ImGui::Text("Bonk Engine | Flashlight");
            ImGui::SameLine(ImGui::GetWindowSize().x - style.FramePadding.x - ImGui::CalcTextSize("JustDiverse on Discord").x);
            ImGui::TextDisabled("JustDiverse on Discord");
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

void RadarGUI()
{
    RenderRadar();
}

void GUIScheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    style.WindowRounding = 4;
    style.ChildRounding = 4;
    style.FrameRounding = 3;
    style.PopupRounding = 3;
    style.GrabRounding = 3;
    style.TabRounding = 3;
    style.ScrollbarRounding = 3;
    style.ButtonTextAlign = { 0.5f, 0.5f };
    style.WindowTitleAlign = { 0.5f, 0.5f };
    style.ItemSpacing = { 9.0f, 9.0f };
    style.WindowPadding = { 9.0f, 9.0f };
    style.FramePadding = { 6.0f, 6.0f };
    style.ItemInnerSpacing = { 8.0f, 8.0f };
    style.WindowBorderSize = 1;
    style.FrameBorderSize = 1;
    style.ScrollbarSize = 12.f;
    style.GrabMinSize = 8.f;

    style.Colors[ImGuiCol_WindowBg] = ImAdd->Hex2RGBA(0x111111, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImAdd->Hex2RGBA(0x151515, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImAdd->Hex2RGBA(0x191919, 1.0f);

    style.Colors[ImGuiCol_Border] = ImAdd->Hex2RGBA(0x1F1F1F, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImAdd->Hex2RGBA(0x1F1F1F, 1.0f);

    style.Colors[ImGuiCol_SliderGrab] = ImAdd->Hex2RGBA(0x5E61BA, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImAdd->Hex2RGBA(0x5E61BA, 0.8f);

    style.Colors[ImGuiCol_CheckMark] = ImAdd->Hex2RGBA(0xE8E8E8, 1.0f);
    style.Colors[ImGuiCol_Text] = ImAdd->Hex2RGBA(0xE8E8E8, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImAdd->Hex2RGBA(0x616161, 1.0f);


    style.Colors[ImGuiCol_Header] = ImAdd->Hex2RGBA(0x212121, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImAdd->Hex2RGBA(0x444444, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImAdd->Hex2RGBA(0x363636, 1.0f);

    style.Colors[ImGuiCol_FrameBg] = ImAdd->Hex2RGBA(0x111111, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImAdd->Hex2RGBA(0x111111, 0.9f);
    style.Colors[ImGuiCol_FrameBgActive] = ImAdd->Hex2RGBA(0x111111, 0.8f);

    style.Colors[ImGuiCol_Button] = ImAdd->Hex2RGBA(0x111111, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImAdd->Hex2RGBA(0x111111, 0.8f);
    style.Colors[ImGuiCol_ButtonActive] = ImAdd->Hex2RGBA(0x111111, 0.6f);
}