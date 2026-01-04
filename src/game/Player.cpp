#include "Player.h"
#include "../core/WeaponData.h"
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

uintptr_t Player::GetWeaponAddress(int id) {

    if (id < 1 || id > 11) {
        return 0;
    }

    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t player_base = *(uintptr_t*)player_pointer;

    uintptr_t weapon_pointer = (player_base + Offsets::WEAPON_ARRAY_START) + (0x18 * id);

    return weapon_pointer;
}

uintptr_t Player::GetWantedLevelAddress(){
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t wanted_class_address = *(uintptr_t*)player_pointer;
    if (wanted_class_address < 0x10000) return 0;

    wanted_class_address = *(uintptr_t*)(wanted_class_address + Offsets::WANTED_LEVEL_ADDRESS);

    uintptr_t stars_address = (wanted_class_address + Offsets::WANTED_LEVEL_STARS_OFFSET);

    return stars_address;
}

uintptr_t Player::Get_Z_Axis_VelocityAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t z_vel_address = *(uintptr_t*)player_pointer;
    if (z_vel_address < 0x10000) return 0;

    z_vel_address += Offsets::Z_VELOCITY_OFFSET;

    return z_vel_address;
}

uintptr_t Player::Get_X_Axis_VelocityAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t x_vel_address = *(uintptr_t*)player_pointer;
    if (x_vel_address < 0x10000) return 0;

    x_vel_address += Offsets::X_VELOCITY_OFFSET;

    return x_vel_address;
}

uintptr_t Player::Get_Y_Axis_VelocityAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t y_vel_address = *(uintptr_t*)player_pointer;
    if (y_vel_address < 0x10000) return 0;

    y_vel_address += Offsets::Y_VELOCITY_OFFSET;

    return y_vel_address;
}

uintptr_t Player::Get_X_VectorAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t forward_address = *(uintptr_t*)player_pointer;
    if (forward_address < 0x10000) return 0;

    forward_address += Offsets::PLAYER_X_VECTOR;

    return forward_address;
}

uintptr_t Player::Get_Y_VectorAddress() {
    uintptr_t moduleBase = Utils::GetModuleBase();
    if (!moduleBase) return 0;

    uintptr_t player_pointer = (moduleBase + Offsets::PLAYER_PED_PTR);

    uintptr_t forward_address = *(uintptr_t*)player_pointer;
    if (forward_address < 0x10000) return 0;

    forward_address += Offsets::PLAYER_Y_VECTOR;

    return forward_address;
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

int Player::GetWantedLevel() {
    uintptr_t addr = GetWantedLevelAddress();
    if (addr)
        return *(int*) addr;
    return 0;
}

void Player::GetWeapon(WeaponInfo weapon) {
    uintptr_t weaponAddress = Player::GetWeaponAddress(weapon.id);
    if (weaponAddress) {
        *(int*)(weaponAddress) = weapon.id;
        *(int*)(weaponAddress + 0x08) = weapon.clipCapacity;
        *(int*)(weaponAddress + 0x0C) = weapon.defaultAmmo;
    }
}

void Player::SetAmmo(WeaponInfo weapon, int amount) {
    uintptr_t weaponAddress = Player::GetWeaponAddress(weapon.id);
    if (weaponAddress) {
        *(int*)(weaponAddress + 0x0C) = amount;
    }
}

void Player::SetWantedLevel(int stars) {
    if (stars > 6) stars = 6;
    if (stars < 0) stars = 0;
    uintptr_t addr = GetWantedLevelAddress();
    int chaos = 0;
    if (addr) {
        switch (stars) {
            case 0: chaos = 0; break;
            case 1: chaos = 70; break;
            case 2: chaos = 250; break;
            case 3: chaos = 450; break;
            case 4: chaos = 900; break;
            case 5: chaos = 1800; break;
            case 6: chaos = 3500; break;
        }
       *(int*)addr = stars;
       uintptr_t chaosAddress = addr - 0x18;
       *(int*)chaosAddress = chaos;
    }
}

void Player::Set_Z_Axis_Velocity(float vel) {
    uintptr_t z_vel_address = Player::Get_Z_Axis_VelocityAddress();
    if (z_vel_address) {
        *(float*)z_vel_address = vel;
    }
}

float Player::Get_Z_Axis_Velocity() {
    uintptr_t z_vel_address = Player::Get_Z_Axis_VelocityAddress();
    if (z_vel_address) {
        return *(float*)z_vel_address;
    }
    return 0;
}

void Player::Set_X_Axis_Velocity(float vel) {
    uintptr_t x_vel_address = Player::Get_X_Axis_VelocityAddress();
    if (x_vel_address) {
        *(float*)x_vel_address = vel;
    }
}

float Player::Get_X_Axis_Velocity() {
    uintptr_t x_vel_address = Player::Get_X_Axis_VelocityAddress();
    if (x_vel_address) {
        return *(float*)x_vel_address;
    }
    return 0;
}

void Player::Set_Y_Axis_Velocity(float vel) {
    uintptr_t y_vel_address = Player::Get_Y_Axis_VelocityAddress();
    if (y_vel_address) {
        *(float*)y_vel_address = vel;
    }
}

float Player::Get_Y_Axis_Velocity() {
    uintptr_t y_vel_address = Player::Get_Y_Axis_VelocityAddress();
    if (y_vel_address) {
        return *(float*)y_vel_address;
    }
    return 0;
}

float Player::Get_X_Vector() {
    uintptr_t forward_vector_address = Player::Get_X_VectorAddress();
    if (forward_vector_address) {
        return *(float*)forward_vector_address;
    }
    return 0;
}

float Player::Get_Y_Vector() {
    uintptr_t forward_vector_address = Player::Get_Y_VectorAddress();
    if (forward_vector_address) {
        return *(float*)forward_vector_address;
    }
    return 0;
}