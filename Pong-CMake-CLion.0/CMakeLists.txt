cmake_minimum_required(VERSION 3.15)
project(Pong-v.2.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic")

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    set(LIBRARY_PATH /usr/src/)
    set(LIBRARY_INCLUDE_PATH /usr/include/SDL2)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    set(LIBRARY_PATH /usr/local/lib)
    set(LIBRARY_INCLUDE_PATH /usr/local/include/SDL2)
else ()
    message(FATAL_ERROR "Error: Your system is unsupported")
endif()

set(INCLUDE_PATH includes/)
set(SOURCE_PATH srcs/)
set(EXECUTABLE Pong-v.2.0)

add_executable(${EXECUTABLE} srcs/main.cpp srcs/PongMenu.cpp srcs/Multiplayer.cpp srcs/SinglePlayer.cpp
                             srcs/Object.cpp srcs/View.cpp srcs/Ball.cpp srcs/Racket.cpp srcs/Bot.cpp
                             srcs/Text.cpp srcs/Tutorial.cpp srcs/Settings.cpp)

target_include_directories(${EXECUTABLE}
        PRIVATE ${INCLUDE_PATH}
        PRIVATE ${LIBRARY_INCLUDE_PATH})

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    target_link_options(${EXECUTABLE} PRIVATE -Wl,-rpath=${LIBRARY_PATH})
elseif (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    target_link_options(${EXECUTABLE} PRIVATE -Wl,-rpath,${LIBRARY_PATH})
endif()

target_link_directories(${EXECUTABLE} PRIVATE ${LIBRARY_PATH})

target_link_libraries(${EXECUTABLE} SDL2 SDL2_image SDL2_mixer SDL2_ttf)
