// ImGuiHook.h (FINAL VERSION)
#pragma once
#include <windows.h>
#include <d3d9.h>
#include "Menu.h"
#include "MinHook.h" 

// Define VK_F5 for clarity
#ifndef VK_F5
#define VK_F5 0x74
#endif

// ----------------------------------------------------
// Globals
// ----------------------------------------------------
typedef HRESULT(__stdcall* EndSceneFn)(LPDIRECT3DDEVICE9);
extern EndSceneFn oEndScene; // MinHook Original EndScene pointer

typedef BOOL (WINAPI *SetCursorPosFn)(int X, int Y);
extern SetCursorPosFn oSetCursorPos;

// Hooked function prototype
BOOL WINAPI hkSetCursorPos(int X, int Y);

extern bool imguiInitialized;
extern bool showMenu;
extern HWND gameWindow;

extern int g_FrameCounter; // Frame Counter
extern WNDPROC oWndProc;   // Original WndProc pointer

// Function Prototypes
LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace UI
{
    void Init();
    void DrawMenu();
}

// Function to log messages (defined in main.cpp)
void Log(const char* msg);