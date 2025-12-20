#include "Menu.h"
#include "imgui.h"
#include <algorithm>
#include "../core/VehicleData.h"
#include "../game/Vehicles.h"
#include "../game/Player.h"

void UI::DrawMenu()
{
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);

    static bool open = true;
    ImGui::Begin("GTA III Trainer", &open, ImGuiWindowFlags_None);

    ImGui::Text("Press F5 to toggle menu");
    ImGui::Separator();
    ImGui::Spacing();

    // ───────── Tabs ─────────
    if (ImGui::BeginTabBar("MainTabs"))
    {
        // ================= PLAYER TAB =================
        if (ImGui::BeginTabItem("Player"))
        {
            // Health
            static float health;
            if (!ImGui::IsAnyItemActive())
                health = Player::GetHealth();

            ImGui::InputFloat("Health", &health);
            if (ImGui::IsItemDeactivatedAfterEdit())
                Player::SetHealth(std::clamp(health, 0.0f, 9999.0f));

            // Armor
            static float armor;
            if (!ImGui::IsAnyItemActive())
                armor = Player::GetArmor();

            ImGui::InputFloat("Armor", &armor);
            if (ImGui::IsItemDeactivatedAfterEdit())
                Player::SetArmor(std::clamp(armor, 0.0f, 9999.0f));

            // Money
            static int money;
            if (!ImGui::IsAnyItemActive())
                money = Player::GetMoney();

            ImGui::InputInt("Money", &money);
            if (ImGui::IsItemDeactivatedAfterEdit())
                Player::SetMoney(std::clamp(money, 0, 999999999));

            // ───── Position Section ─────
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Text("Position");
            ImGui::Separator();
            ImGui::Spacing();

            static float x, y, z;

            if (!ImGui::IsAnyItemActive())
            {
                x = Player::Get_X_Axis();
                y = Player::Get_Y_Axis();
                z = Player::Get_Z_Axis();
            }

            ImGui::PushItemWidth(150);

            ImGui::InputFloat("X", &x);
            if (ImGui::IsItemDeactivatedAfterEdit())
                Player::Set_X_Axis(x);

            ImGui::InputFloat("Y", &y);
            if (ImGui::IsItemDeactivatedAfterEdit())
                Player::Set_Y_Axis(y);

            ImGui::InputFloat("Z", &z);
            if (ImGui::IsItemDeactivatedAfterEdit())
                Player::Set_Z_Axis(z);

            ImGui::PopItemWidth();

            ImGui::EndTabItem();
        }

        // ================= VEHICLES TAB =================
        if (ImGui::BeginTabItem("Vehicles"))
        {
            static int selectedIdx = 0;      // Index in our VEHICLE_LIST
            static int manualId = 90;        // Manual ID input
            static float errorTimer = 0.0f;

            ImGui::Text("Vehicle Spawner");
            ImGui::Separator();
            ImGui::Spacing();

            // ─── Dropdown Selection ───
            if (ImGui::BeginCombo("Select Vehicle", VEHICLE_LIST[selectedIdx].name.c_str()))
            {
                for (int n = 0; n < VEHICLE_LIST.size(); n++)
                {
                    const bool is_selected = (selectedIdx == n);
                    if (ImGui::Selectable(VEHICLE_LIST[n].name.c_str(), is_selected)) {
                        selectedIdx = n;
                        manualId = VEHICLE_LIST[n].id; // Sync manual ID box with dropdown
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            // ─── Manual ID Input ───
            ImGui::PushItemWidth(100);
            if (ImGui::InputInt("Manual ID", &manualId)) {
                // Optional: find index in list to sync dropdown back
                for(int i=0; i < VEHICLE_LIST.size(); i++) {
                    if(VEHICLE_LIST[i].id == manualId) { selectedIdx = i; break; }
                }
            }
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // ─── Spawn Button ───
            if (ImGui::Button("Spawn Selected", ImVec2(150, 30)))
            {
                // We trust the manualId box to be the final authority
                if (manualId >= 90 && manualId <= 150)
                {
                    Vehicles::SpawnVehicle((uint8_t)manualId);
                }
                else
                {
                    errorTimer = ImGui::GetTime() + 3.0f;
                }
            }

            if (ImGui::GetTime() < errorTimer) {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Invalid ID! (Must be 90-150)");
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
