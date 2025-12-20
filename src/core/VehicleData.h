#pragma once
#include <string>
#include <vector>

struct VehicleInfo {
    int id;
    std::string name;
};

const std::vector<VehicleInfo> VEHICLE_LIST = {
    { 90, "Landstalker" }, { 91, "Idaho" }, { 92, "Stinger" }, { 93, "Linerunner" },
    { 94, "Perennial" }, { 95, "Sentinel" }, { 96, "Patriot" }, { 97, "Firetruck" },
    { 98, "Trashmaster" }, { 99, "Stretch" }, { 100, "Manana" }, { 101, "Infernus" },
    { 102, "Blista" }, { 103, "Pony" }, { 104, "Mule" }, { 105, "Cheetah" },
    { 106, "Ambulance" }, { 107, "FBI Car" }, { 108, "Moonbeam" }, { 109, "Esperanto" },
    { 110, "Taxi" }, { 111, "Kuruma" }, { 112, "Bobcat" }, { 113, "Mr Whoopee" },
    { 114, "BF Injection" }, { 115, "Corpse (Manana)" }, { 116, "Police" },
    { 117, "Enforcer" }, { 118, "Securicar" }, { 119, "Banshee" }, { 121, "Bus" },
    { 122, "Rhino" }, { 123, "Barracks OL" }, { 124, "Train" }, { 127, "Coach" },
    { 128, "Cabbie" }, { 129, "Stallion" }, { 130, "Rumpo" }, { 131, "RC Bandit" },
    { 132, "Belly Up (Triad Fish Van)" }, { 133, "Mr Wongs" }, { 134, "Mafia Sentinel" },
    { 135, "Yardie Lobo" }, { 136, "Yakuza Stinger" }, { 137, "Diablo Stallion" },
    { 138, "Cartel Cruiser" }, { 139, "Hoods Rumpo XL" }, { 144, "Panlantic" },
    { 145, "Flatbed" }, { 146, "Yankee" }, { 148, "Borgnine" }, { 149, "Toyz" }
};