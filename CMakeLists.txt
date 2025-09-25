cmake_minimum_required(VERSION 3.20)
project(FarmSim)

include(GNUInstallDirs)

option(SHOW_HITBOX "Draw hitbox boundaries" OFF)

if (NOT TARGET rygame)
    find_package(rygame REQUIRED)
endif ()

add_executable(
    ${PROJECT_NAME}
    code/main.cpp
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
    code/Menu.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE rygame)

if (WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE "/WX")
else ()
    # set(CMAKE_CXX_COMPILER "clang++") # Sprite::Kill() has [[nodiscard]]
    # target_compile_options(${PROJECT_NAME} PRIVATE "-fsanitize=address")
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE "-Wall"
        "-Werror"
        "-Wpedantic"
        "-Wno-missing-braces"
        "-Wno-gnu-anonymous-struct"
        "-Wno-nested-anon-types")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-unused-variable")
    endif ()
endif ()

if (SHOW_HITBOX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SHOW_HITBOX)
endif ()

# copy resources to Build folder for debugging
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

option(INSTALL_GAME "Whether or not to install the game" OFF)
if (INSTALL_GAME)
    install(TARGETS ${PROJECT_NAME})
    # copy resources to Install location
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR})
endif ()

if (EMSCRIPTEN)
    target_link_options(
        ${PROJECT_NAME}
        PRIVATE
        -sALLOW_MEMORY_GROWTH=1
        -sEXPORTED_RUNTIME_METHODS=[requestFullscreen]
        -sUSE_GLFW=3
        --shell-file
        "$ENV{EMSCRIPTEN}/src/shell.html")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    set(resources_dir ${CMAKE_CURRENT_SOURCE_DIR}/resources)
    if (EXISTS ${resources_dir})
        # The local resources path needs to be mapped to /resources virtual path
        string(APPEND resources_dir "@resources")
        target_link_options(
            ${PROJECT_NAME}
            PRIVATE
            --preload-file
            "${resources_dir}")
    endif ()
endif ()
