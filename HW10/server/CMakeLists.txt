cmake_minimum_required(VERSION 3.20)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp)

target_link_libraries(server wsock32)
target_link_libraries(server ws2_32)