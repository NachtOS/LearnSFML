cmake_minimum_required(VERSION 4.1)
project(SfmlLearn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(app main.cpp
        Player.cpp
        Player.h
        Coin.cpp
        Coin.h
        Enemy.cpp
        Enemy.h
        Entity.cpp
        Entity.h)

add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:app>/assets)

target_link_libraries(app PRIVATE SFML::Graphics)
