cmake_minimum_required (VERSION 3.22)

project (
    LeoSim
    VERSION 0.1
    DESCRIPTION "A simulator for the Léo homebrew computer"
    LANGUAGES CXX)

# Libraries

# Moira 68k CPU simulator
add_subdirectory(libs/moira)
# Simple DirectMedia Layer graphics library (release-2.28.x branch)
add_subdirectory(libs/SDL)
include_directories(libs/SDL/include)
# Dear ImGui library (docking branch + custom CMakeLists.txt)
add_subdirectory(libs/imgui)
include_directories(libs/imgui)
include_directories(libs/imgui/backends)

# Main executable

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)


# Link static libraries to main executable

target_link_libraries(
    ${PROJECT_NAME}
    SDL2-static
    imgui
)