#pragma once

typedef HRESULT(APIENTRY* Present_t)(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
extern Present_t Present;
typedef void(APIENTRY* ExecuteCommandLists_t)(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists);
extern ExecuteCommandLists_t ExecuteCommandLists;

namespace DX12
{
	extern HWND hwnd;
	extern WNDPROC WndProc;

	extern ID3D12Device* Device;
	extern ID3D12DescriptorHeap* DescriptorHeapBackBuffers;
	extern ID3D12DescriptorHeap* DescriptorHeapImGuiRender;
	extern ID3D12GraphicsCommandList* CommandList;
	extern ID3D12CommandQueue* CommandQueue;

	struct _FrameContext
	{
		ID3D12CommandAllocator* CommandAllocator;
		ID3D12Resource* Resource;
		D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHandle;
	};

	LRESULT __stdcall MainProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT APIENTRY Present_f(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
	void ExecuteCommandLists_f(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists);

}

extern bool RenderMenu;

extern bool bEnableESP;
extern int iESPToggle;
extern bool bNearbyPlayers;

extern bool bTeamNames;
extern bool bTeamHealth;
extern bool bTeamClass;
extern bool bTeamWeapon;
extern bool bTeamDistance;
extern bool bTeamSnaplines;
extern bool bTeamSkeleton;
extern bool bTeamViewAngle;
extern bool bTeamBoxs; extern int iSelectedTeamBox;

extern ImColor cTeamNames;
extern ImColor cTeamHealth;
extern ImColor cTeamClass;
extern ImColor cTeamWeapon;
extern ImColor cTeamDistance;
extern ImColor cTeamSnaplines;
extern ImColor cTeamSkeleton;
extern ImColor cTeamViewAngles;
extern ImColor cTeamBoxs;

extern bool bEnemyNames;
extern bool bEnemyHealth;
extern bool bEnemyClass;
extern bool bEnemyWeapon;
extern bool bEnemyDistance;
extern bool bEnemySnaplines;
extern bool bEnemySkeleton;
extern bool bEnemyViewAngle;
extern bool bEnemyBoxs; extern int iSelectedEnemyBox;

extern ImColor cEnemyNames;
extern ImColor cEnemyHealth;
extern ImColor cEnemyClass;
extern ImColor cEnemyWeapon;
extern ImColor cEnemyDistance;
extern ImColor cEnemySnaplines;
extern ImColor cEnemySkeleton;
extern ImColor cEnemyViewAngles;
extern ImColor cEnemyBoxs;

extern bool bMonsters;
extern bool bMonsterHealth;
extern bool bMonsterDistance;
extern ImColor cMonsters;

extern bool bFloorPortal;
extern ImColor cFloorPortal;

extern int iItemDistance;
extern bool bRenderItems;

extern int iDistanceCheckSlider;
extern bool bChests;
extern ImColor cChests;

extern bool bTraps;
extern ImColor cTraps;

extern bool bRadar;
extern float RadarX;
extern float RadarY;
extern float RadarSize;
extern float RadarZoom;

extern bool bPlayerStatList;
extern bool bAlter;
extern ImColor cAlter;




extern bool bAimbot; extern int iAimBone;
extern bool bShowFOV; extern float sFOVSize; extern ImColor cFOVColor;
extern int iAimType;
extern bool bAimSmoothness; extern float sAimSmoothness;
extern bool bAimSmoothRandom;
extern bool bTargetTeamates;
extern bool bDrawTargetLine ;
extern bool bDrawTargetName;
extern int iAimKey;
extern ImColor cTargetLine;
extern ImColor cTargetName;





extern bool bPlayerFeatures;
extern bool bFullbright;
extern float fFOV;
extern bool bFreeCam;