#pragma once
#include <cstdint>

class Player {
public:
    static uintptr_t GetHealthAddress();
    static uintptr_t GetArmorAddress();
    static uintptr_t GetMoneyAddress();
    static uintptr_t Get_X_Axis_Address();
    static uintptr_t Get_Y_Axis_Address();
    static uintptr_t Get_Z_Axis_Address();
    

    static void SetHealth(float value);
    static void SetArmor(float value);
    static void SetMoney(int value);
    static void Set_X_Axis(float value);
    static void Set_Y_Axis(float value);
    static void Set_Z_Axis(float value);
    static float GetHealth();
    static float GetArmor();
    static int GetMoney();
    static float Get_X_Axis();
    static float Get_Y_Axis();
    static float Get_Z_Axis();
};
