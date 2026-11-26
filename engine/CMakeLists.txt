file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(engine STATIC ${ENGINE_SOURCES})
    target_include_directories(engine PUBLIC include)
    target_link_libraries(engine PRIVATE
        common
        SFML::Graphics SFML::Window SFML::System
        ImGui-SFML::ImGui-SFML
    )