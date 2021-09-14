cmake_minimum_required(VERSION 3.20)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client main.cpp)
target_link_libraries(client wsock32)
target_link_libraries(client ws2_32)