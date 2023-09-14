#include "pch.h"
#include "DX12.h"
#include "DirectX/ImGuiExtras/Font.h"

Present_t Present;
ExecuteCommandLists_t ExecuteCommandLists;
IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool should_ignore_msg(UINT msg)
{
	switch (msg)
	{
	case WM_MOUSEACTIVATE:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_MOUSEMOVE:
	case WM_NCHITTEST:
	case WM_MOUSEWHEEL:
	case WM_MOUSEHOVER:
	case WM_ACTIVATEAPP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_SETCURSOR:
		return true;
	default:
		return false;
	}
}

#pragma region MenuVars

	bool RenderMenu = false;

#pragma endregion

#pragma region ESPVars

bool bEnableESP = false;
int iESPToggle = VK_F2;
float RadarX = 100.0f;
float RadarY = 100.0;
bool bNearbyPlayers = false;

bool bTeamNames = false;
bool bTeamHealth = false;
bool bTeamClass = false;
bool bTeamWeapon = false;
bool bTeamDistance = false;
bool bTeamSnaplines = false;
bool bTeamSkeleton = false;
bool bTeamViewAngle = false;
bool bTeamBoxs = false;
int iSelectedTeamBox = 0;
ImColor cTeamNames = { 32, 172, 0, 255 };
ImColor cTeamHealth = { 38, 181, 50, 255 };
ImColor cTeamClass = { 255, 255, 255, 255 };
ImColor cTeamWeapon = { 255, 255, 255, 255 };
ImColor cTeamDistance = { 181, 163, 29, 255 };
ImColor cTeamSnaplines = { 32, 172, 0, 255 };
ImColor cTeamSkeleton = { 32, 172, 0, 255 };
ImColor cTeamViewAngles = { 255, 255, 255, 255 };
ImColor cTeamBoxs = { 32, 172, 0, 255 };

bool bEnemyNames = false;
bool bEnemyHealth = false;
bool bEnemyClass = false;
bool bEnemyWeapon = false;
bool bEnemyDistance = false;
bool bEnemySnaplines = false;
bool bEnemySkeleton = false;
bool bEnemyViewAngle = false;
bool bEnemyBoxs = false;
int iSelectedEnemyBox = 0;
ImColor cEnemyNames = { 145, 26, 7, 255 };
ImColor cEnemyHealth = { 38, 181, 50, 255 };
ImColor cEnemyClass = { 255, 255, 255, 255 };
ImColor cEnemyWeapon = { 255, 255, 255, 255 };
ImColor cEnemyDistance = { 181, 163, 29, 255 };
ImColor cEnemySnaplines = { 145, 26, 7, 255 };
ImColor cEnemySkeleton = { 145, 26, 7, 255 };
ImColor cEnemyViewAngles = { 255, 255, 255, 255 };
ImColor cEnemyBoxs = { 145, 26, 7, 255 };

bool bMonsters = false; 
bool bMonsterHealth = false;
bool bMonsterDistance = false;
ImColor cMonsters = { 255, 142, 0, 255 };

bool bFloorPortal = false;
ImColor cFloorPortal = { 255, 0, 255, 255 };

int iItemDistance = 50;
bool bRenderItems = false;

int iDistanceCheckSlider = 50;
bool bChests = false;
ImColor cChests = { 0, 255, 201, 255 };

bool bTraps = false;
ImColor cTraps = { 0, 44, 255, 255 };

bool bRadar = false;
float RadarSize = 250.0f;
float RadarZoom = 1.0f;

bool bPlayerStatList = false;
bool bAlter = false;
ImColor cAlter = { 255, 0, 255, 255 };

#pragma endregion

#pragma region AimbotVars

bool bAimbot = false;
int iAimBone = 0;
bool bShowFOV = false; float sFOVSize = { 270.0f }; ImColor cFOVColor = { 255, 255, 255, 255 };
int iAimType = 0;
bool bAimSmoothness = false; float sAimSmoothness = { 15.0f };
bool bAimSmoothRandom = false;
bool bTargetTeamates = false;
bool bDrawTargetLine = false;
bool bDrawTargetName = false;
int iAimKey = VK_INSERT;
ImColor cTargetLine = { 255, 255, 255, 255 };
ImColor cTargetName = { 255, 255, 255, 255 };
#pragma endregion

#pragma region ExploitVars

bool bPlayerFeatures = false;
bool bFullbright = false;
float fFOV = 90.f;
bool bFreeCam = false;

#pragma endregion

void draw_bone_names(ADCCharacterBase* actor)
{
	printf("enum bones{\n");
	for (auto i = 0; i < 200; i++)
	{
		auto location = actor->Mesh->GetSocketLocation(actor->Mesh->GetBoneName(i));
		auto bone_name = actor->Mesh->GetBoneName(i);

		nlog("%s = %d,\n", bone_name.GetName().data(), i);
	}
}

namespace DX12
{
	HWND hwnd = nullptr;
	WNDPROC WndProc;

	ID3D12Device* Device;
	ID3D12DescriptorHeap* DescriptorHeapBackBuffers;
	ID3D12DescriptorHeap* DescriptorHeapImGuiRender;
	ID3D12GraphicsCommandList* CommandList;
	ID3D12CommandQueue* CommandQueue;

	uint64_t BuffersCounts = -1;
	_FrameContext* FrameContext;

	void ExecuteCommandLists_f(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists)
	{
		if (!CommandQueue)
			CommandQueue = queue;

		spoof_call(ExecuteCommandLists, queue, NumCommandLists, ppCommandLists);
	}

	LRESULT __stdcall MainProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		{
			if (uMsg == WM_KEYUP && wParam == VK_F5)
			{
				RenderMenu = !RenderMenu;
				ImGui::GetIO().MouseDrawCursor = RenderMenu;
				return 0;
			}

			if (uMsg == WM_KEYDOWN && wParam == VK_F5)
				return 0;

			if (RenderMenu)
			{
				LRESULT result = ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

				return TRUE;
			}

			return CallWindowProcA(DX12::WndProc, hWnd, uMsg, wParam, lParam);
		}
	}

	std::once_flag onStart;
	HRESULT APIENTRY Present_f(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		std::call_once(onStart, [&]()
			{
				if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&Device))) {
					ImGui::CreateContext();

					ImGuiIO& io = ImGui::GetIO(); (void)io;
					ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
					io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

					DXGI_SWAP_CHAIN_DESC Desc;
					pSwapChain->GetDesc(&Desc);
					Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
					Desc.OutputWindow = hwnd;
					Desc.Windowed = ((GetWindowLongPtr(hwnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

					BuffersCounts = Desc.BufferCount;
					FrameContext = new _FrameContext[BuffersCounts];

					D3D12_DESCRIPTOR_HEAP_DESC DescriptorImGuiRender = {};
					DescriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
					DescriptorImGuiRender.NumDescriptors = BuffersCounts;
					DescriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

					if (Device->CreateDescriptorHeap(&DescriptorImGuiRender, IID_PPV_ARGS(&DescriptorHeapImGuiRender)) != S_OK)
						return Present(pSwapChain, SyncInterval, Flags);

					ID3D12CommandAllocator* Allocator;
					if (Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&Allocator)) != S_OK)
						return Present(pSwapChain, SyncInterval, Flags);

					for (size_t i = 0; i < BuffersCounts; i++) {
						FrameContext[i].CommandAllocator = Allocator;
					}

					D3D12_COMMAND_QUEUE_DESC QueueDesc;
					QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
					QueueDesc.Priority = 0;
					QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
					QueueDesc.NodeMask = 0;

					ID3D12CommandQueue* CommandQueueL;
					if (Device->CreateCommandQueue(&QueueDesc, __uuidof(ID3D12CommandQueue), (void**)&CommandQueueL) < 0) {
						return Present(pSwapChain, SyncInterval, Flags);
					}

					ID3D12CommandAllocator* CommandAllocator;
					if (Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&CommandAllocator) < 0) {
						return Present(pSwapChain, SyncInterval, Flags);
					}

					ID3D12GraphicsCommandList* local_cmd_list;
					if (Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&local_cmd_list) < 0) {
						return Present(pSwapChain, SyncInterval, Flags);
					}

					if (Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, Allocator, NULL, IID_PPV_ARGS(&CommandList)) != S_OK ||
						CommandList->Close() != S_OK)
						return Present(pSwapChain, SyncInterval, Flags);

					D3D12_DESCRIPTOR_HEAP_DESC DescriptorBackBuffers;
					DescriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
					DescriptorBackBuffers.NumDescriptors = BuffersCounts;
					DescriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
					DescriptorBackBuffers.NodeMask = 1;

					if (Device->CreateDescriptorHeap(&DescriptorBackBuffers, IID_PPV_ARGS(&DescriptorHeapBackBuffers)) != S_OK)
						return Present(pSwapChain, SyncInterval, Flags);

					const auto RTVDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
					D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle = DescriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();

					for (size_t i = 0; i < BuffersCounts; i++) {
						ID3D12Resource* pBackBuffer = nullptr;
						FrameContext[i].DescriptorHandle = RTVHandle;
						pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
						Device->CreateRenderTargetView(pBackBuffer, nullptr, RTVHandle);
						FrameContext[i].Resource = pBackBuffer;
						RTVHandle.ptr += RTVDescriptorSize;
					}

					DXGI_RATIONAL RefreshRate;
					RefreshRate.Numerator = 60;
					RefreshRate.Denominator = 1;

					DXGI_MODE_DESC BufferDesc;
					BufferDesc.Width = 100;
					BufferDesc.Height = 100;
					BufferDesc.RefreshRate = RefreshRate;
					BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
					BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

					DXGI_SAMPLE_DESC SampleDesc;
					SampleDesc.Count = 1;
					SampleDesc.Quality = 0;

					uint64_t* MethodsTable = (uint64_t*)::calloc(150, sizeof(uint64_t));
					memcpy(MethodsTable, *(uint64_t**)Device, 44 * sizeof(uint64_t));
					memcpy(MethodsTable + 44, *(uint64_t**)CommandQueueL, 19 * sizeof(uint64_t));
					memcpy(MethodsTable + 44 + 19, *(uint64_t**)CommandAllocator, 9 * sizeof(uint64_t));
					memcpy(MethodsTable + 44 + 19 + 9, *(uint64_t**)local_cmd_list, 60 * sizeof(uint64_t));

					ExecuteCommandLists = (ExecuteCommandLists_t)MethodsTable[54];

					ImGui_ImplWin32_Init(hwnd);
					ImGui_ImplDX12_Init(Device, BuffersCounts, DXGI_FORMAT_R8G8B8A8_UNORM, DescriptorHeapImGuiRender, DescriptorHeapImGuiRender->GetCPUDescriptorHandleForHeapStart(), DescriptorHeapImGuiRender->GetGPUDescriptorHandleForHeapStart());
					ImGui_ImplDX12_CreateDeviceObjects();
					ImGui::GetIO().ImeWindowHandle = hwnd;

					GUIScheme();

					DetourStart(ExecuteCommandLists, ExecuteCommandLists_f);

					ImGui::GetIO().WantSaveIniSettings = false;
					ImGui::GetIO().IniFilename = NULL;

					SetupCircles();
				}

			});

		if (CommandQueue == nullptr)
			return Present(pSwapChain, SyncInterval, Flags);

		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		RenderText({ 10, 10 }, { 255,255,255,255 }, Xors("[!] Bonk Engine | Dark and Darker"));
		if (RenderMenu) {
			RenderGUI();
		}

		if (bRadar)
		{
			RadarGUI();
		}
		ImGui::End();

		ImGui::EndFrame();

		if (bEnableESP) {
			ESP();
		}
		
		if (GetAsyncKeyState(iESPToggle))
		{
			bEnableESP != bEnableESP;
		}

		if (bAimbot) {
			Aimbot();
		}

		if (bPlayerFeatures) {
			PlayerFeatures();
		}

		if (bShowFOV)
		{
			RenderCirc({ ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 }, sFOVSize, cFOVColor, 1.0f);
		}

		_FrameContext& CurrentFrameContext = FrameContext[pSwapChain->GetCurrentBackBufferIndex()];
		CurrentFrameContext.CommandAllocator->Reset();

		D3D12_RESOURCE_BARRIER Barrier;
		Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		Barrier.Transition.pResource = CurrentFrameContext.Resource;
		Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		CommandList->Reset(CurrentFrameContext.CommandAllocator, nullptr);
		CommandList->ResourceBarrier(1, &Barrier);
		CommandList->OMSetRenderTargets(1, &CurrentFrameContext.DescriptorHandle, FALSE, nullptr);
		CommandList->SetDescriptorHeaps(1, &DescriptorHeapImGuiRender);

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), CommandList);
		Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		CommandList->ResourceBarrier(1, &Barrier);
		CommandList->Close();
		CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&CommandList));

		return spoof_call(Present, pSwapChain, SyncInterval, Flags);
	}
}