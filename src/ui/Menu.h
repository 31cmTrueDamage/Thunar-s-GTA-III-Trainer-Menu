#pragma once
namespace UI {
    void DrawMenu();

    namespace Cheats {
        inline bool godMode = false;
        inline bool infiniteAmmo = false;
        inline bool neverWanted = false;
        inline bool superJump = false;
        inline float jumpMultiplier = 0;
        inline float jumpXYMultiplier = 0;
        inline float fallSpeed = 0;
        inline int selectedPreset = 0;
        inline bool flyMode = fallSpeed;
        inline float flySpeed = 0;
    }
}
