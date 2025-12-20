#include "Utils.h"
#include <windows.h>

uintptr_t Utils::GetModuleBase() {
    return (uintptr_t)GetModuleHandleA(nullptr); 
}

uint8_t* Utils::getCaveSpace(size_t size) {
    uint8_t* caveSpace = (uint8_t*)VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    return caveSpace;
}