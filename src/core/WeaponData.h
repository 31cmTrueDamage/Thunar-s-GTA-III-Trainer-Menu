#ifndef WEAPONDATA_H
#define WEAPONDATA_H

#include <string>
#include <vector>

struct WeaponInfo {
    int id;
    std::string name;
    int clipCapacity;
    int defaultAmmo;
};

namespace WeaponData {
    inline WeaponInfo Bat        = { 1,  "Baseball Bat",    1,  1 };
    inline WeaponInfo Pistol     = { 2,  "Colt 45",         12, 68 };
    inline WeaponInfo Uzi        = { 3,  "Uzi",             25, 150 };
    inline WeaponInfo Shotgun    = { 4,  "Shotgun",         20,  30 };
    inline WeaponInfo AK47       = { 5,  "AK-47",           30, 150 };
    inline WeaponInfo M4         = { 6,  "M4",              60, 250 };
    inline WeaponInfo Sniper     = { 7,  "Sniper Rifle",    1,  20 };
    inline WeaponInfo Rocket     = { 8,  "Rocket Launcher", 1,  10 };
    inline WeaponInfo Flame      = { 9,  "Flamethrower",    500, 500 };
    inline WeaponInfo Molotov    = { 10, "Molotov",         1,  10 };
    inline WeaponInfo Grenade    = { 11, "Grenade",         1,  10 };

    inline std::vector<WeaponInfo> WEAPON_LIST = {
        Bat, Pistol, Uzi, Shotgun, AK47, M4, Sniper, Rocket, Flame, Molotov, Grenade
    };
}

#endif