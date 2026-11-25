file(GLOB COMMON_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(common STATIC ${COMMON_SOURCES})
    target_include_directories(common PUBLIC include)
    target_link_libraries(common
        PRIVATE SFML::Graphics SFML::Window SFML::System
    )