cmake_minimum_required(VERSION 3.25)
project(gamr)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(gamr main.cpp)
target_link_libraries(gamr sfml-graphics sfml-audio)