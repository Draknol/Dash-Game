file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(DashEditor ${EDITOR_SOURCES})

target_include_directories(DashEditor PRIVATE include)

target_link_libraries(DashEditor
    PRIVATE engine SFML::Graphics SFML::Window SFML::System ImGui-SFML::ImGui-SFML
)

add_custom_command(TARGET DashEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:DashEditor>/res
)