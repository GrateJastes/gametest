cmake_minimum_required(VERSION 3.20)

project(gametest)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics network audio)

include_directories(.)

add_executable(game
        gametest/main.cpp
        gametest/Application.cpp
        gametest/Entity.cpp
        gametest/Aircraft.cpp
        gametest/SceneNode.cpp
        gametest/SpriteNode.cpp
        gametest/World.cpp
        gametest/Command.cpp
        gametest/CommandQueue.cpp
        gametest/Player.cpp
        gametest/StateStack.cpp gametest/State.cpp gametest/State.hpp gametest/GameState.cpp gametest/GameState.hpp gametest/TitleState.cpp gametest/TitleState.hpp gametest/Utility.cpp gametest/Utility.hpp gametest/MenuState.cpp gametest/MenuState.hpp)

target_link_libraries(game
        ${SFML_LIBRARIES}
        ${SFML_DEPENDENCIES})
