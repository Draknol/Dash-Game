cmake_minimum_required(VERSION 4.5.0)
project(DashGame)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    URL      https://github.com/SFML/SFML/archive/refs/tags/3.1.0.tar.gz
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    imgui
    URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.1.tar.gz
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_DIR ${imgui_SOURCE_DIR})

FetchContent_Declare(
    imgui-sfml
    URL https://github.com/SFML/imgui-sfml/archive/refs/tags/v3.0.tar.gz
)
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_MakeAvailable(imgui-sfml)

add_subdirectory(common)
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(game)