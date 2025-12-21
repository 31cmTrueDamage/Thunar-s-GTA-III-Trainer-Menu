# GTA III Internal Trainer (v0.2)

An internal mod menu for **Grand Theft Auto III (Steam)** using ImGui and Minhook.
All Memory Addresses used have been manually found by me without searching them online, as i also wanted to improve my RE skills, i did occasionally check the re3 repo to look at the already reverse engineered code, to sort of see how the game works in certain aspects.

---

## ✨ Features

- **Player Module:**
  - Health & Armor editing.
  - Money manipulation.
  - Godmode
  - Never Wanted
  - Set Wanted Level
  - Coordinate-based Teleportation (X, Y, Z).
- **Vehicle Module:**
  - Vehicle Spawner.
  - **The "Rhino Exploit":** The Spawner modifies the GIVEUSATANK cheat to be able to spawn any wheeled vehicle, to fully function, i created a codecave and redirected the execution towards it, this had to be done since it could only spawn ids up until 127, which i presume was due to a compiler optimization since the rhino id was 122.
- **Weapon Module:**
    - Weapon spawning
    - Includes options as set ammo, set infinite ammo, get all weapons at once.
- **UI:**
  - Toggle visibility with the **F5** key.

## 🚀 Building from Source

This project uses **CMake** and **MinGW-w64**.

### Prerequisites
* **CMake** (3.10+)
* **MinGW-w64** (GCC/G++) installed and added to System PATH.

### Compilation

1. **Clone the repository:**
```bash
   git clone https://github.com/31cmTrueDamage/Thunar-s-GTA-III-Trainer-Menu.git
   cd Thunar-s-GTA-III-Trainer-Menu
```

2. **Generate the build files:**
   Run the following in the root folder. If your compilers are not in your PATH, you can specify them manually as shown:
```bash
   # Standard way (if in PATH):
   cmake -B build -G "MinGW Makefiles"

   # Manual way (if not in PATH):
   cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
```

3. **Compile the DLL:**
```bash
   cmake --build build
```

The compiled `GTA3Trainer.dll` will be located in the `/build` directory.

---

## 📋 Usage

1. Launch GTA III (v1.0).
2. Use a DLL Injector of your choice to inject `GTA3Trainer.dll` (I used XENOS, but any should work).
3. Press **F5** in-game to open the menu.
4. Have fun

---

## 🛡️ Disclaimer

This project is for educational and research purposes only. It is intended to showcase memory management and assembly-level programming within legacy game engines. Use responsibly.
