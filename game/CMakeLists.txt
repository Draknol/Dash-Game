cmake_minimum_required(VERSION 4.5.0)
file(GLOB GAME_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(DashGame ${GAME_SOURCES})

target_include_directories(DashGame PRIVATE include)

target_link_libraries(DashGame PRIVATE
    common
    engine
    SFML::Graphics SFML::Window SFML::System
    ImGui-SFML::ImGui-SFML
)

add_custom_command(TARGET DashGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:DashGame>/res
)