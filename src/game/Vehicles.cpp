#include "Vehicles.h"
#include "Offsets.h"
#include "Utils.h"
#include <windows.h>

void WriteJmp(uintptr_t addressToWrite, uintptr_t addressToJumpTo) {
    uint8_t jmpOp[5] = { 0xE9, 0, 0, 0, 0 };
    *(uint32_t*)(jmpOp + 1) = (uint32_t)(addressToJumpTo - (addressToWrite + 5));
    DWORD old;
    VirtualProtect((LPVOID)addressToWrite, 5, PAGE_EXECUTE_READWRITE, &old);
    memcpy((void*)addressToWrite, jmpOp, 5);
    VirtualProtect((LPVOID)addressToWrite, 5, old, &old);
}

void Vehicles::SpawnVehicle(uint8_t vehicleID) {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return;

    uint8_t* caveSpace = Utils::getCaveSpace(128);
    if (!caveSpace) return;

    uint8_t* caveRequest = caveSpace;
    uint8_t* caveCreate = caveSpace + 64;

    uintptr_t addrRequest = moduleBase + 0x90F01;
    uintptr_t funcRequest = moduleBase + 0x7EA0;
    uintptr_t returnRequest = moduleBase + 0x90F08;
    
    uintptr_t addrCreate = moduleBase + 0x90F84;
    uintptr_t funcCreate = moduleBase + 0x12C6B0;
    uintptr_t returnCreate = moduleBase + 0x90F8B;
    
    uintptr_t cheatMgr = *(uintptr_t*)(moduleBase + 0x4F43A4);
    uintptr_t funcSpawn = moduleBase + 0x90EE0;

    // Build Cave_Request
    int idx = 0;
    caveRequest[idx++] = 0x68; // push vehicleID
    *(uint32_t*)&caveRequest[idx] = (uint32_t)vehicleID;
    idx += 4;
    caveRequest[idx++] = 0xE8; // call funcRequest
    *(int32_t*)&caveRequest[idx] = (int32_t)(funcRequest - ((uintptr_t)caveRequest + idx + 4));
    idx += 4;
    caveRequest[idx++] = 0xE9; // jmp returnRequest
    *(int32_t*)&caveRequest[idx] = (int32_t)(returnRequest - ((uintptr_t)caveRequest + idx + 4));

    // Build Cave_Create
    idx = 0;
    caveCreate[idx++] = 0x68; // push vehicleID
    *(uint32_t*)&caveCreate[idx] = (uint32_t)vehicleID;
    idx += 4;
    caveCreate[idx++] = 0xE8; // call funcCreate
    *(int32_t*)&caveCreate[idx] = (int32_t)(funcCreate - ((uintptr_t)caveCreate + idx + 4));
    idx += 4;
    caveCreate[idx++] = 0xE9; // jmp returnCreate
    *(int32_t*)&caveCreate[idx] = (int32_t)(returnCreate - ((uintptr_t)caveCreate + idx + 4));

    // Mark cave as executable
    DWORD oldProtect;
    VirtualProtect(caveSpace, 128, PAGE_EXECUTE_READWRITE, &oldProtect);

    // Save original bytes
    uint8_t og1[7], og2[7];
    memcpy(og1, (void*)addrRequest, 7);
    memcpy(og2, (void*)addrCreate, 7);

    // Hook Request
    WriteJmp(addrRequest, (uintptr_t)caveRequest);
    DWORD old;
    VirtualProtect((LPVOID)(addrRequest + 5), 2, PAGE_EXECUTE_READWRITE, &old);
    memset((void*)(addrRequest + 5), 0x90, 2);
    VirtualProtect((LPVOID)(addrRequest + 5), 2, old, &old);

    // Hook Create
    WriteJmp(addrCreate, (uintptr_t)caveCreate);
    VirtualProtect((LPVOID)(addrCreate + 5), 2, PAGE_EXECUTE_READWRITE, &old);
    memset((void*)(addrCreate + 5), 0x90, 2);
    VirtualProtect((LPVOID)(addrCreate + 5), 2, old, &old);

    // Trigger spawn
    __asm__ __volatile__ (
        "push %%eax\n\t"
        "push %%edx\n\t"
        "movl %0, %%ecx\n\t"
        "call *%1\n\t"
        "pop %%edx\n\t"
        "pop %%eax\n\t"
        :
        : "r" (cheatMgr), "r" (funcSpawn)
        : "ecx", "memory"
    );

    // Restore original bytes
    VirtualProtect((LPVOID)addrRequest, 7, PAGE_EXECUTE_READWRITE, &old);
    memcpy((void*)addrRequest, og1, 7);
    VirtualProtect((LPVOID)addrRequest, 7, old, &old);
    
    VirtualProtect((LPVOID)addrCreate, 7, PAGE_EXECUTE_READWRITE, &old);
    memcpy((void*)addrCreate, og2, 7);
    VirtualProtect((LPVOID)addrCreate, 7, old, &old);

    // Don't free the cave immediately - add a small delay
    Sleep(100);
    VirtualFree(caveSpace, 0, MEM_RELEASE);
}
