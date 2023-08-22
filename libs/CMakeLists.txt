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

# set(MOIRA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/moira)
# add_subdirectory(${MOIRA_DIR})