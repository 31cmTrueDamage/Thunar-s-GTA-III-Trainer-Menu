#pragma once

namespace Offsets {
    // Base pointer chain for player

    constexpr uintptr_t PLAYER_PED_PTR = 0x2FB1C8;

    constexpr uintptr_t HEALTH = 0x2C0;

    constexpr uintptr_t ARMOR = 0x2C4;

    constexpr uintptr_t PLAYER_X_VECTOR = 0x14;
    
    constexpr uintptr_t PLAYER_Y_VECTOR = 0x18;

    constexpr uintptr_t MOVEMENT_TYPE = 0x22C;

    constexpr uintptr_t WANTED_LEVEL_ADDRESS = 0x53C;

    constexpr uintptr_t WANTED_LEVEL_STARS_OFFSET = 0x18;

    constexpr uintptr_t X_POS = 0x34;

    constexpr uintptr_t Y_POS = 0x38;

    constexpr uintptr_t Z_POS = 0x3C;

    constexpr uintptr_t MONEY = 0x54139C;

    constexpr uintptr_t CHEAT_MANAGER_PTR = 0x4F43A4;

    // It's actually the tank spawning function through GIVEUSATANK cheat <3
    constexpr uintptr_t SPAWN_VEHICLE_FUNCTION = 0x90EE0;

    // ID passed to Request Model function i presume
    constexpr uintptr_t RHINO_ID_PATCH_1 = 0x90F01;

    // Request Model Function
    constexpr uintptr_t REQUEST_MODEL_FUNCTION = 0x7EA0;

    // ID passed to Vehicle CONSTRUCTOR i think or add To World
    constexpr uintptr_t RHINO_ID_PATCH_2 = 0x90F84;

    constexpr uintptr_t CREATE_MODEL_FUNCTION = 0X12CB60;

    constexpr uintptr_t WEAPON_ARRAY_START = 0x35C;

    constexpr uintptr_t WEAPON_BAT = 0x374;
    constexpr uintptr_t WEAPON_PISTOL = 0x38C;
    constexpr uintptr_t WEAPON_SMG = 0x3A4;
    constexpr uintptr_t WEAPON_SHOTGUN = 0x3BC;
    constexpr uintptr_t WEAPON_AK = 0x3D4;
    constexpr uintptr_t WEAPON_M4 = 0x3EC;
    constexpr uintptr_t WEAPON_SNIPER = 0x404;
    constexpr uintptr_t WEAPON_ROCKET_LAUNCHER = 0x41C;
    constexpr uintptr_t WEAPON_FLAMETHROWER = 0x434;
    constexpr uintptr_t WEAPON_MOLOTOV = 0x44C;
    constexpr uintptr_t WEAPON_GRENADE = 0x464;

    constexpr uintptr_t Z_VELOCITY_OFFSET = 0x80;
    constexpr uintptr_t X_VELOCITY_OFFSET = 0x7C;
    constexpr uintptr_t Y_VELOCITY_OFFSET = 0x78;
}