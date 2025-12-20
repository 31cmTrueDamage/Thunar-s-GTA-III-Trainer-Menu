#define _CRT_STDIO_INLINE
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h> // Required for strlen
#include "ui/ImGuiHook.h" // Assuming this is the path to your header

void CreateConsole()
{
    // Allocates a new console for the calling process
    AllocConsole();

    // Redirect standard streams to the new console
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);

    // Set console title
    SetConsoleTitleA("GTA III Trainer Debug Console");

    std::cout << "[DEBUG] Console Allocated Successfully" << std::endl;
}

// ----------------------------------------------------
// Log function (SIMPLIFIED for maximum stability)
// ----------------------------------------------------
void Log(const char* msg)
{
    // Log file will be created in the current working directory.
    // Ensure the game is running from a writable directory.
    HANDLE hFile = CreateFileA(
        "gta3_trainer_simple.log",
        FILE_APPEND_DATA,
        FILE_SHARE_READ,
        nullptr,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (hFile == INVALID_HANDLE_VALUE)
        return;

    // Optional: Add a simple time stamp
    SYSTEMTIME st;
    GetLocalTime(&st);
    char timeBuf[64];
    int len = wsprintfA(timeBuf, "[%02d:%02d:%02d] ", st.wHour, st.wMinute, st.wSecond);
    
    DWORD written;
    WriteFile(hFile, timeBuf, len, &written, nullptr);
    
    // Write the actual message
    WriteFile(hFile, msg, (DWORD)strlen(msg), &written, nullptr);
    WriteFile(hFile, "\r\n", 2, &written, nullptr);

    CloseHandle(hFile);
}

// Global cleanup function (for MinHook)
void Cleanup()
{
    // These functions must be defined in your ImGuiHook.cpp
    extern void CleanupHooks();
    CleanupHooks(); 
    Log("DLL cleanup complete.");
}

// ----------------------------------------------------
// Init Thread
// ----------------------------------------------------
DWORD WINAPI InitThread(LPVOID)
{

    CreateConsole();
    Log("InitThread: started");
    MessageBoxA(nullptr, "GTA3 Trainer injected!", "OK", MB_OK);

    Log("InitThread: before UI::Init (D3D9 Hook Attempt)");
    UI::Init();
    Log("InitThread: after UI::Init (D3D9 Hook Complete)");

    return 0;
}

// ----------------------------------------------------
// DllMain Entry Point
// ----------------------------------------------------
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        Log("DllMain: PROCESS_ATTACH");
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        Cleanup(); 
        Log("DllMain: PROCESS_DETACH");
    }
    return TRUE;
}