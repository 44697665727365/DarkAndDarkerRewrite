#ifndef PCH_H
#define PCH_H
#define IMGUI_DEFINE_MATH_OPERATORS

// add headers that you want to pre-compile here
#include "framework.h"

#define IM_ARRAYSIZETEAM(arr1)		(sizeof(arr1) / sizeof((arr1)[0]))
#define IM_ARRAYSIZEENEMY(arr2)		(sizeof(arr2) / sizeof((arr2)[0]))
#define IM_ARRAYSIZEAIMBONE(arr3)	(sizeof(arr3) / sizeof((arr3)[0]))
#define IM_ARRAYSIZEAIMTYPE(arr4)	(sizeof(arr4) / sizeof((arr4)[0]))

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Hooking/detours.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "urlmon.lib")

using namespace std::chrono_literals;
using namespace std::literals;

#pragma warning( disable : 4244 ) //Disable int to float warning
#pragma warning( disable : 4267 ) //Disable size_t to int warning
#pragma warning( disable : 4305 ) //Disable double to float warning
#pragma warning( disable : 26495 ) //Disable Variable uninitalized for my ui stuff
#pragma warning( disable : 26812 ) //Disable enum type is unscoped

#define DetourStart(sym, des) \
DetourUpdateThread(GetCurrentThread());\
DetourTransactionBegin(); \
DetourAttach(&(LPVOID&)sym, des); \
DetourTransactionCommit(); \

#define DetourRemove(sym, des) \
DetourUpdateThread(GetCurrentThread());\
DetourTransactionBegin(); \
DetourDetach(&(LPVOID&)sym, des); \
DetourTransactionCommit(); \

#include "Protection/LazyImport.h"
#include "Protection/Xors.h"
//#include "Protection/json.h"

#include "Utilities/memory.h"
#include "Utilities/string.h"
#include "Utilities/spoof_call.h"

#include "DirectX/ImGui/imgui.h"
#include "DirectX/ImGui/imgui_impl_dx12.h"
#include "DirectX/ImGui/imgui_impl_win32.h"
#include "DirectX/ImGui/imgui_stdlib.h"

#include "DirectX/DX12.h"

#include "UnrealEngine/UnrealEngine.h"
#include "SDK/SDK.h"
#include "Hooking/Hooks.h"

#include "DirectX/ImGuiExtras/Constellation.h"
#include "Helpers/Aimbot/AAHelpers.h"
#include "Helpers/Aimbot/AimAssist.h"
#include "Helpers/ESP/ESPHelpers.h"
#include "Helpers/ESP/ExtraSensoryPerception.h"
#include "Helpers/GUI/GUI.h"
#include "Helpers/Features/PlayerFeatures.h"
#include "Helpers/Rendering/Rendering.h"

#endif //PCH_H