cmake_minimum_required(VERSION 4.5.0)
project(DashGame)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    URL      https://github.com/SFML/SFML/archive/refs/tags/3.1.0.tar.gz
)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")

add_executable(DashGame ${SOURCES})

target_include_directories(DashGame PRIVATE include)

target_link_libraries(DashGame PRIVATE SFML::Graphics SFML::Window SFML::System)

add_custom_command(TARGET DashGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:DashGame>/res
)