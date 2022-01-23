cmake_minimum_required(VERSION 3.20)

project(gametest)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics network audio)

include_directories(include)
include_directories(src)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_executable(game
        src/main.cpp
        src/Game.cpp
        src/Entity.cpp
        src/Aircraft.cpp
        src/SceneNode.cpp)

target_link_libraries(game
        ${SFML_LIBRARIES}
        ${SFML_DEPENDENCIES})
