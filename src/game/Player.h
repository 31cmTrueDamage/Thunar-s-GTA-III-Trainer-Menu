#pragma once
#include <cstdint>
#include "../core/WeaponData.h"

class Player {
    
public:
    static uintptr_t GetHealthAddress();
    static uintptr_t GetArmorAddress();
    static uintptr_t GetMoneyAddress();
    static uintptr_t Get_X_Axis_Address();
    static uintptr_t Get_Y_Axis_Address();
    static uintptr_t Get_Z_Axis_Address();
    static uintptr_t GetWeaponAddress(int id);
    static uintptr_t GetWantedLevelAddress();
    static uintptr_t Get_Z_Axis_VelocityAddress();
    static uintptr_t Get_X_Axis_VelocityAddress();
    static uintptr_t Get_Y_Axis_VelocityAddress();
    static uintptr_t Get_X_VectorAddress();
    static uintptr_t Get_Y_VectorAddress();


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
    static void GetWeapon(WeaponInfo weapon);
    static void SetAmmo(WeaponInfo weapon, int amount);
    static int GetWantedLevel();
    static void SetWantedLevel(int level);
    static void Set_Z_Axis_Velocity(float velocity);
    static float Get_Z_Axis_Velocity();
    static void Set_X_Axis_Velocity(float velocity);
    static float Get_X_Axis_Velocity();
    static void Set_Y_Axis_Velocity(float velocity);
    static float Get_Y_Axis_Velocity();
    static float Get_X_Vector();
    static float Get_Y_Vector();

};
