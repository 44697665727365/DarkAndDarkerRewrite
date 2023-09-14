#include "pch.h"

void RenderLobbyList()
{
    auto draw = ImGui::GetBackgroundDrawList();

    SanityChecks();

    auto game_state = UWorld::Singleton()->GameState;
    if (!game_state) return;

    auto base_state = reinterpret_cast<ADCGameStateBase*>(game_state);
    if (!base_state) return;

    auto data_array = base_state->AccountDataReplicationArray;

    for (int i = 0; i < data_array.Num(); i++)
    {
        if (!data_array.IsValidIndex(i)) break;
        auto player_data = data_array[i];

        auto name = player_data.Nickname.OriginalNickName;
        if (!name.IsValid()) return;
        auto player_name = name.ToString();

        FString cname = player_data.Nickname.StreamingModeNickName;
        std::string _name = cname.ToString();

        size_t hash_pos = _name.find('#');
        std::string class_name = _name.substr(0, hash_pos);

        auto level = player_data.Level;

        auto has_left = player_data.bExit;

        auto is_alive = player_data.bAlive;

        std::string info;
        ImColor color;
        ImColor outline_color = { 0, 0, 0, 255 };

        info = player_name + " - Lvl: " + std::to_string(level) + " " + class_name + " | DEAD";
        color = { 181, 0, 24, 255 };

        if (is_alive)
        {
            info = player_name + " - Lvl: " + std::to_string(level) + " " + class_name + " | ALIVE";
            color = { 40, 252, 3, 255 };

            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f - 1, 200.f + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f + 1, 200.f + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f - 1 + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f + 1 + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);

            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f + (20.f * i)), color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            continue;
        }

        if (has_left)
        {
            info = player_name + " - Lvl: " + std::to_string(level) + " " + class_name + " | DISCONNECTED";
            color = { 122, 121, 119, 220 };

            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f - 1, 200.f + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f + 1, 200.f + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f - 1 + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f + 1 + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);

            draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f + (20.f * i)), color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
            continue;
        }

        draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f - 1, 200.f + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
        draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f + 1, 200.f + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
        draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f - 1 + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
        draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f + 1 + (20.f * i)), outline_color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);

        draw->AddText(ImGui::GetIO().FontDefault, 18, ImVec2(50.f, 200.f + (20.f * i)), color, info.c_str(), info.c_str() + info.size(), 0.0f, 0);
    }
}

void PlayerFeatures()
{
    SanityChecks();

    if (bFullbright)
    {
        ULocalPlayer::Singleton()->ViewportClient->ViewModeIndex = 1;
    }

    if (bPlayerStatList)
    {
        RenderLobbyList();
    }
}