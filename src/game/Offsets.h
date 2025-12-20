#pragma once

namespace Offsets {
    // Base pointer chain for player

    constexpr uintptr_t PLAYER_PED_PTR = 0x2FB1C8;

    constexpr uintptr_t HEALTH = 0x2C0;

    constexpr uintptr_t ARMOR = 0x2C4;

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

}