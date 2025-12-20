#include "Hotkeys.h"
#include <windows.h>
#include <thread>
#include <chrono>

std::map<int, std::function<void()>> Hotkeys::callbacks;

void Hotkeys::Register(int vkCode, std::function<void()> callback) {
    callbacks[vkCode] = callback;
}

void Hotkeys::Run() {
    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        for (const auto& pair : callbacks) {
            if (GetAsyncKeyState(pair.first) & 1) {
                pair.second();
            }
        }

        Sleep(50);
    }
}