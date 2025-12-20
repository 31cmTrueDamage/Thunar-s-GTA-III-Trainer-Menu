#pragma once
#include <windows.h>
#include <functional>
#include <map>

class Hotkeys {
public:
    static void Register(int vkCode, std::function<void()> callback);
    static void Run();

private:
    static std::map<int, std::function<void()>> callbacks;
};