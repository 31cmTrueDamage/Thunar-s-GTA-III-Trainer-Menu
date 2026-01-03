#include <windows.h>
#include <d3d9.h>
#include "ImGuiHook.h" 
#include "Menu.h"      

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "../game/Player.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ----------------------------------------------------
// Globals
// ----------------------------------------------------
EndSceneFn oEndScene = nullptr;
WNDPROC oWndProc = nullptr;
SetCursorPosFn oSetCursorPos = nullptr;

bool imguiInitialized = false;
bool showMenu = true;
HWND gameWindow = nullptr;
int g_FrameCounter = 0; 

static bool g_WndProcInstalled = false;

// ----------------------------------------------------
// Hooked SetCursorPos
// ----------------------------------------------------
BOOL WINAPI hkSetCursorPos(int X, int Y)
{
    if (showMenu)
        return TRUE;
    
    return oSetCursorPos(X, Y);
}

// ----------------------------------------------------
// Hooked WndProc - WITH EXTENSIVE LOGGING
// ----------------------------------------------------
LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Log EVERYTHING when menu is open
    static int logCounter = 0;
    
    if (showMenu)
    {
        // Log first few messages of each type
        if (logCounter < 5)
        {
            char buf[128];
            wsprintfA(buf, "hkWndProc CALLED: msg=0x%X, wParam=0x%X", uMsg, wParam);
            Log(buf);
            logCounter++;
        }
        
        // Always log important messages
        if (uMsg == WM_LBUTTONDOWN)
        {
            Log("hkWndProc: *** WM_LBUTTONDOWN RECEIVED ***");
        }
        
        if (uMsg == WM_MOUSEMOVE)
        {
            static int moveCount = 0;
            moveCount++;
            if (moveCount % 60 == 0)
            {
                Log("hkWndProc: Mouse is moving");
            }
        }
    }
    else
    {
        logCounter = 0;
    }
    
    // F5 toggle always passes through
    if ((uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) && wParam == VK_F5)
    {
        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
    }

    // Let ImGui handle input when menu is open
    if (showMenu)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        {
            if (uMsg == WM_LBUTTONDOWN)
            {
                Log("hkWndProc: ImGui consumed the click!");
            }
            return true;
        }
        
        // Block game input
        switch (uMsg)
        {
            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONDBLCLK:
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            case WM_MOUSEWHEEL:
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_CHAR:
                return true;
        }
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

// ----------------------------------------------------
// EndScene Hook - FIXED WINDOW DETECTION
// ----------------------------------------------------
HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 device)
{
    g_FrameCounter++;
    
    if (!imguiInitialized)
    {
        Log("=== IMGUI INIT START ===");
        
        // Get the actual device window instead of foreground window
        D3DDEVICE_CREATION_PARAMETERS params;
        if (SUCCEEDED(device->GetCreationParameters(&params)))
        {
            gameWindow = params.hFocusWindow;
            
            char buf[128];
            wsprintfA(buf, "Device window handle: 0x%X", (DWORD)(DWORD_PTR)gameWindow);
            Log(buf);
            
            // Verify window is valid
            if (!IsWindow(gameWindow))
            {
                Log("ERROR: Invalid window handle!");
                return oEndScene(device);
            }
            
            char className[256];
            GetClassNameA(gameWindow, className, 256);
            wsprintfA(buf, "Window class: %s", className);
            Log(buf);
        }
        else
        {
            Log("ERROR: Could not get device creation parameters!");
            gameWindow = GetForegroundWindow();
        }
        
        if (!gameWindow)
        {
            Log("ERROR: No valid window handle!");
            return oEndScene(device);
        }
        
        // Create ImGui context
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(gameWindow);
        ImGui_ImplDX9_Init(device);
        
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        
        // Larger UI
        io.FontGlobalScale = 1.0f;
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(1.0f);
        
        Log("ImGui initialized, installing WndProc hook...");
        
        // Install WndProc hook
        LONG_PTR result = SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
        
        if (result == 0)
        {
            DWORD error = GetLastError();
            char buf[128];
            wsprintfA(buf, "ERROR: SetWindowLongPtr failed with error: %d", error);
            Log(buf);
        }
        else
        {
            oWndProc = (WNDPROC)result;
            g_WndProcInstalled = true;
            
            char buf[128];
            wsprintfA(buf, "WndProc hook installed! Old: 0x%p, New: 0x%p", oWndProc, hkWndProc);
            Log(buf);
            
            // Verify the hook stuck
            LONG_PTR current = GetWindowLongPtrA(gameWindow, GWLP_WNDPROC);
            if (current == (LONG_PTR)hkWndProc)
            {
                Log("WndProc hook VERIFIED successfully!");
            }
            else
            {
                Log("WARNING: WndProc hook verification FAILED!");
            }
        }

        imguiInitialized = true;
        Log("=== IMGUI INIT COMPLETE ===");
    }
    
    // Check if WndProc is still hooked (some games unhook it)
    if (g_WndProcInstalled && gameWindow)
    {
        static int checkCounter = 0;
        checkCounter++;
        
        if (checkCounter % 300 == 0) // Check every 5 seconds at 60fps
        {
            LONG_PTR current = GetWindowLongPtrA(gameWindow, GWLP_WNDPROC);
            if (current != (LONG_PTR)hkWndProc)
            {
                Log("WARNING: WndProc was unhooked! Reinstalling...");
                oWndProc = (WNDPROC)SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
            }
        }
    }

    // Menu toggle
    if (GetAsyncKeyState(VK_F5) & 1) 
    {
        showMenu = !showMenu;
        Log(showMenu ? "*** MENU OPENED ***" : "*** MENU CLOSED ***");
    }
    
    // Start ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (Player::GetHealthAddress() != 0) 
    {
        if (UI::Cheats::godMode) 
        {
            Player::SetHealth(100.0f);
            Player::SetArmor(100.0f);
        }

        if (UI::Cheats::infiniteAmmo) 
        {
            for (const auto& weapon : WeaponData::WEAPON_LIST) 
            {
                Player::SetAmmo(weapon, 999);
            }
        }

        if (UI::Cheats::neverWanted)
        {
            Player::SetWantedLevel(0);
        }

        if (UI::Cheats::superJump)
        {
            static bool jumped = false;
            float zVel = Player::Get_Z_Axis_Velocity();
            float xVel = Player::Get_X_Axis_Velocity();
            float yVel = Player::Get_Y_Axis_Velocity();

            if (zVel > 0.08f && zVel < 0.11f && !jumped) {
                Player::Set_Z_Axis_Velocity(zVel * UI::Cheats::jumpMultiplier);
                if (abs(xVel) > 0.01f) Player::Set_X_Axis_Velocity(xVel * UI::Cheats::jumpXYMultiplier);
                if (abs(yVel) > 0.01f) Player::Set_Y_Axis_Velocity(yVel * UI::Cheats::jumpXYMultiplier);
                jumped = true;
            }

            if (zVel < -0.05f) {
                Player::Set_Z_Axis_Velocity(UI::Cheats::fallSpeed);
            }

            if (abs(zVel) < 0.001f) {
                jumped = false; 
            }
        }

        if (UI::Cheats::flyMode)
        {
            Player::Set_X_Axis_Velocity(0.0f);
            Player::Set_Y_Axis_Velocity(0.0f);
            Player::Set_Z_Axis_Velocity(0.0f);

            float s = UI::Cheats::flySpeed;

            if (GetAsyncKeyState('W') & 0x8000) Player::Set_X_Axis_Velocity(s);
            if (GetAsyncKeyState('S') & 0x8000) Player::Set_X_Axis_Velocity(-s);
            if (GetAsyncKeyState('D') & 0x8000) Player::Set_Y_Axis_Velocity(s);
            if (GetAsyncKeyState('A') & 0x8000) Player::Set_Y_Axis_Velocity(-s);

            if (GetAsyncKeyState(VK_SPACE) & 0x8000) Player::Set_Z_Axis_Velocity(s);
            if (GetAsyncKeyState(VK_MENU) & 0x8000) Player::Set_Z_Axis_Velocity(-s);
        }
    }
    
    // Cursor management
    ImGuiIO& io = ImGui::GetIO();
    
    if (showMenu)
    {
        io.MouseDrawCursor = true;
        
        int cursorCount = ShowCursor(TRUE);
        while (cursorCount < 0)
            cursorCount = ShowCursor(TRUE);
        
        SetCursor(LoadCursor(NULL, IDC_ARROW));
    }
    else
    {
        io.MouseDrawCursor = false;
        
        int cursorCount = ShowCursor(FALSE);
        while (cursorCount >= 0)
            cursorCount = ShowCursor(FALSE);
    }

    // Render
    if (showMenu)
        UI::DrawMenu();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData()); 

    return oEndScene(device); 
}

// ----------------------------------------------------
// Init Function
// ----------------------------------------------------
void UI::Init()
{
    Log("=== UI::Init START ===");
    
    if (MH_Initialize() != MH_OK)
    {
        Log("ERROR: MH_Initialize failed!");
        return;
    }
    Log("MinHook initialized");
    
    // Hook SetCursorPos
    void* pTargetSetCursorPos = (void*)GetProcAddress(GetModuleHandleA("user32.dll"), "SetCursorPos");
    
    if (pTargetSetCursorPos)
    {
        if (MH_CreateHook(pTargetSetCursorPos, (LPVOID)hkSetCursorPos, (LPVOID*)&oSetCursorPos) == MH_OK)
        {
            if (MH_EnableHook(pTargetSetCursorPos) == MH_OK)
            {
                Log("SetCursorPos hook enabled");
            }
        }
    }
    
    Log("Waiting for d3d9.dll...");
    while (!GetModuleHandleA("d3d9.dll"))
        Sleep(100);
    Log("d3d9.dll found!");

    IDirect3D9* d3d = nullptr;
    IDirect3DDevice9* device = nullptr;
    void* pTargetEndScene = nullptr; 

    Log("Getting EndScene address...");
    while (!pTargetEndScene)
    {
        HWND hwnd = GetForegroundWindow();
        if (!hwnd) 
        {
            Sleep(100);
            continue;
        }

        d3d = Direct3DCreate9(D3D_SDK_VERSION);
        if (!d3d) 
        {
            Sleep(100);
            continue;
        }

        D3DPRESENT_PARAMETERS pp{};
        pp.Windowed = TRUE;
        pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        pp.hDeviceWindow = hwnd;

        if (SUCCEEDED(d3d->CreateDevice(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            hwnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &pp,
            &device)))
        {
            void** vtable = *(void***)device;
            pTargetEndScene = vtable[42];

            char buf[128];
            wsprintfA(buf, "EndScene address: 0x%p", pTargetEndScene);
            Log(buf);

            device->Release();
            d3d->Release();
            break; 
        }

        if (device) device->Release();
        if (d3d) d3d->Release();
        Sleep(100);
    }
    
    if (pTargetEndScene)
    {
        if (MH_CreateHook(pTargetEndScene, (LPVOID)hkEndScene, (LPVOID*)&oEndScene) != MH_OK)
        {
            Log("ERROR: MH_CreateHook failed!");
            MH_Uninitialize();
            return;
        }

        if (MH_EnableHook(pTargetEndScene) != MH_OK)
        {
            Log("ERROR: MH_EnableHook failed!");
            MH_Uninitialize();
            return;
        }
        
        Log("EndScene hook enabled!");
    }
    
    Log("=== UI::Init COMPLETE ===");
}

// ----------------------------------------------------
// Cleanup
// ----------------------------------------------------
void CleanupHooks()
{
    Log("=== CLEANUP START ===");
    
    if (oWndProc && gameWindow)
    {
        SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
        Log("WndProc restored");
    }
    
    if (imguiInitialized)
    {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    
    Log("=== CLEANUP COMPLETE ===");
}