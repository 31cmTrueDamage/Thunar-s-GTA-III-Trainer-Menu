cmake_minimum_required(VERSION 3.16)
project(gta3_trainer)

set(CMAKE_CXX_STANDARD 17)

# Force 32-bit build (optional, only if you target 32-bit GTA III)
set(CMAKE_C_FLAGS "-m32 -static-libgcc")
set(CMAKE_CXX_FLAGS "-m32 -std=c++17 -static-libgcc -static-libstdc++")

# Static linking flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")

# Add global define to fix _imp____acrt_iob_func
add_definitions(-D_CRT_STDIO_INLINE)

# Include paths
include_directories(
    external/imgui
    external/imgui/backends
    external/minhook/include
    D:/mingw64/i686-w64-mingw32/include  # if really building 32-bit
)

# Source files
add_library(gta3_trainer SHARED
    src/main.cpp
    src/ui/Menu.cpp
    src/ui/ImGuiHook.cpp
    src/game/Player.cpp
    src/game/Vehicles.cpp
    src/game/Utils.cpp

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_dx9.cpp
    external/imgui/backends/imgui_impl_win32.cpp

    external/minhook/src/buffer.c
    external/minhook/src/hook.c
    external/minhook/src/trampoline.c
    external/minhook/src/hde/hde32.c
)

# Link Windows system libraries (static linking for runtime, dynamic for Windows APIs)
target_link_libraries(gta3_trainer
    d3d9
    user32
    gdi32
    kernel32
    advapi32
    ole32
    oleaut32
    comdlg32
)

# Optional: 32-bit target on Windows
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_GENERATOR_PLATFORM Win32)