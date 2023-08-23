#=================== SDL2 ===================

set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL)
add_subdirectory(${SDL2_DIR})

#=================== Dear ImGui ===================

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_library(imgui STATIC)

target_sources(
    imgui
    PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp

    PRIVATE
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

target_include_directories(
    imgui
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    PUBLIC ${SDL2_DIR}/include
)

target_link_libraries(imgui PUBLIC SDL2-static ${CMAKE_DL_LIBS})

#=================== Moira ===================

# Not using add_subdirectory for the Moira directory because we only want to link the CPU and not its tests.

set(MOIRA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/moira/Moira/)
add_library(
    moira
    STATIC
        ${MOIRA_DIR}Moira.cpp
        ${MOIRA_DIR}MoiraDebugger.cpp
        ${MOIRA_DIR}softfloat/softfloat.cpp
)

target_include_directories(
    moira
    PUBLIC ${MOIRA_DIR}
    PUBLIC ${MOIRA_DIR}/softfloat
)

# The following compile options are from MOIRA_DIR/CMakeLists.txt
if (NOT MSVC)
    target_compile_options(moira PUBLIC -Wno-unused-parameter)
    target_compile_options(moira PUBLIC -Wno-unused-but-set-parameter)
    target_compile_options(moira PUBLIC -Wno-unused-but-set-variable)
    target_compile_options(moira PUBLIC -Wno-missing-field-initializers)
endif()
if(MSVC)
    target_compile_options(moira PUBLIC /W4 /bigobj) # /WX disabled for now
    target_compile_options(moira PUBLIC /wd4100 /wd4201 /wd4324 /wd4458 /wd4127)
endif()
if(MINGW)
    target_compile_options(moira PUBLIC -Wa,-mbig-obj)
endif()
