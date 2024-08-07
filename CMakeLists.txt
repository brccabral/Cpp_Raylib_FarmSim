cmake_minimum_required(VERSION 3.20)
project(FarmSim)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)
find_package(rygame REQUIRED)
find_package(tmx REQUIRED)
find_package(raylib-tmx REQUIRED)

add_executable(${PROJECT_NAME} code/main.cpp
        code/Game.cpp
        code/Level.cpp
        code/Player.cpp
        code/Overlay.cpp
        code/CameraGroup.cpp
        code/Sprites/GenericSprite.cpp
        code/Sprites/Water.cpp
        code/Sprites/WildFlower.cpp
        code/Sprites/Tree.cpp
        code/Sprites/Particle.cpp
        code/Sprites/Interaction.cpp
        code/Transition.cpp
        code/SoilLayer.cpp
        code/Sprites/SoilTile.cpp
        code/Sprites/WaterTile.cpp
        code/Rain.cpp
        code/Sprites/Drop.cpp
        code/Sprites/Plant.cpp
        code/Sky.cpp
        code/Menu.cpp
)
target_link_libraries(${PROJECT_NAME} raylib rygame tmx raylib-tmx)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} gdi32 msvcrt winmm)
    set(COMPILE_FLAGS "/NODEFAULTLIB:libcmt")
else ()
    target_link_libraries(${PROJECT_NAME} m)
    #    target_compile_options(${PROJECT_NAME} PRIVATE "-fsanitize=address")
    target_compile_options(${PROJECT_NAME} PRIVATE "-Werror" "-Wreturn-type")
endif ()

if (SHOW_HITBOX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SHOW_HITBOX)
endif ()

# copy resources to Build folder for debugging
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

option(INSTALL_GAME "Whether or not to install the game" OFF)
if (INSTALL_GAME)
    install(TARGETS ${PROJECT_NAME})
    # copy resources to Install location
    install(DIRECTORY
            ${PROJECT_SOURCE_DIR}/resources
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
    )
endif ()
