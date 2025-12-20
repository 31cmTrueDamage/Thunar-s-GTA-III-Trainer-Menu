cmake_minimum_required(VERSION 3.16)
project(gta3_trainer)

set(CMAKE_CXX_STANDARD 17)

# Force 32-bit build
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

# Add global define to fix _imp____acrt_iob_func
add_definitions(-D_CRT_STDIO_INLINE)

# Include paths
include_directories(
    external/imgui
    external/imgui/backends
    external/minhook/include
    D:/mingw64/i686-w64-mingw32/include
)

# Source files
add_library(gta3_trainer SHARED
    src/main.cpp
    src/ui/Menu.cpp
    src/ui/ImGuiHook.cpp
    src/game/Player.cpp
    src/game/Resolver.cpp
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

# Link libraries (XInput added for gamepad support)
target_link_libraries(gta3_trainer
    d3d9
    user32
)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_GENERATOR_PLATFORM Win32) # explicitly 32-bit

set(CMAKE_C_FLAGS "-m32 -static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "-m32 -std=c++17 -static -static-libgcc -static-libstdc++")

link_directories(D:/mingw64/i686-w64-mingw32/lib)
