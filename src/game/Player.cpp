#include "Player.h"
#include "Resolver.h"
#include "Offsets.h"
#include "Utils.h"
#include <windows.h>
#include <cmath>


uintptr_t Player::GetHealthAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t* pMaster = (uintptr_t*)(moduleBase + Offsets::PLAYER_PED_PTR);

    if (IsBadReadPtr(pMaster, sizeof(uintptr_t))) return 0;

    uintptr_t cpedBase = *pMaster;

    if (cpedBase < 0x10000) return 0;

    return cpedBase + Offsets::HEALTH;
}

uintptr_t Player::GetArmorAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t* pMaster = (uintptr_t*)(moduleBase + Offsets::PLAYER_PED_PTR);

    if (IsBadReadPtr(pMaster, sizeof(uintptr_t))) return 0;

    uintptr_t cpedBase = *pMaster;

    if (cpedBase < 0x10000) return 0;

    return cpedBase + Offsets::ARMOR;
}

uintptr_t Player::GetMoneyAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    return moduleBase + Offsets::MONEY;
}

uintptr_t Player::Get_X_Axis_Address() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t* pMaster = (uintptr_t*)(moduleBase + Offsets::PLAYER_PED_PTR);

    if (IsBadReadPtr(pMaster, sizeof(uintptr_t))) return 0;

    uintptr_t cpedBase = *pMaster;

    if (cpedBase < 0x10000) return 0;

    return cpedBase + Offsets::X_POS;
}

uintptr_t Player::Get_Y_Axis_Address() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t* pMaster = (uintptr_t*)(moduleBase + Offsets::PLAYER_PED_PTR);

    if (IsBadReadPtr(pMaster, sizeof(uintptr_t))) return 0;

    uintptr_t cpedBase = *pMaster;

    if (cpedBase < 0x10000) return 0;

    return cpedBase + Offsets::Y_POS;
}

uintptr_t Player::Get_Z_Axis_Address() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t* pMaster = (uintptr_t*)(moduleBase + Offsets::PLAYER_PED_PTR);

    if (IsBadReadPtr(pMaster, sizeof(uintptr_t))) return 0;

    uintptr_t cpedBase = *pMaster;

    if (cpedBase < 0x10000) return 0;

    return cpedBase + Offsets::Z_POS;
}

void Player::Set_X_Axis(float value) {
    uintptr_t addr = Get_X_Axis_Address();
    if (addr)
        *(float*)addr = value;
}

void Player::Set_Y_Axis(float value) {
    uintptr_t addr = Get_Y_Axis_Address();
    if (addr)
        *(float*)addr = value;
}

void Player::Set_Z_Axis(float value) {
    uintptr_t addr = Get_Z_Axis_Address();
    if (addr)
        *(float*)addr = value;
}

void Player::SetHealth(float value) {
    uintptr_t addr = GetHealthAddress();
    if (addr)
        *(float*)addr = value;
}

void Player::SetArmor(float value) {
    uintptr_t addr = GetArmorAddress();
    if (addr)
        *(float*)addr = value;
}

float Player::Get_X_Axis() {
    uintptr_t addr = Get_X_Axis_Address();
    if (addr)
        return *(float*)addr;
    
    return 0.0f;
}

float Player::Get_Y_Axis() {
    uintptr_t addr = Get_Y_Axis_Address();
    if (addr)
        return *(float*)addr;
    
    return 0.0f;
}

float Player::Get_Z_Axis() {
    uintptr_t addr = Get_Z_Axis_Address();
    if (addr)
        return *(float*)addr;
    
    return 0.0f;
}

float Player::GetHealth() {
    uintptr_t addr = GetHealthAddress();
    if (addr)
        return *(float*)addr;

    return 0.0f;
}

float Player::GetArmor() {
    uintptr_t addr = GetArmorAddress();
    if (addr)
        return *(float*)addr;
    return 0.0f;
}

void Player::SetMoney(int value) {
    uintptr_t addr = GetMoneyAddress();
    if (addr)
        *(int*) addr = value;
}

int Player::GetMoney() {
    uintptr_t addr = GetMoneyAddress();
    if (addr)
        return *(int*) addr;
    return 0;
}
