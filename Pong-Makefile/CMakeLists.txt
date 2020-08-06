cmake_minimum_required(VERSION 3.15)
project(Pong_bkuksa)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall")
set(SOURCE_FILES srcs/main.cpp
                    srcs/Controller.cpp
                    srcs/Play.cpp
                    srcs/View.cpp
                    srcs/Pong.cpp)
add_executable(Pong_bkuksa ${SOURCE_FILES})


set(SDL2_INCLUDE_DIR /usr/local/include)
set(SDL2_LIBRARY /usr/local/Celler/sdl2/2.0.12_1)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})