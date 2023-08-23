cmake_minimum_required (VERSION 3.22)

project (
    LeoSim
    VERSION 0.1
    DESCRIPTION "A simulator for the Léo homebrew computer"
    LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Libraries

add_subdirectory("libs")

# Main executable

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} SDL2-static imgui moira)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})