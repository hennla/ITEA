cmake_minimum_required(VERSION 3.20)
project(sb_server)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "D:/CI/repository/boost_1_73_0")
set(BOOSTROOT "D:/CI/repository/boost_1_73_0")

find_package(Boost 1.73.0)

if (Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find boost!")
endif ()

add_executable(sb_server main.cpp PlayerSession.cpp PlayerSession.h PlayerManager.cpp PlayerManager.h Player.h GameServer.cpp GameServer.h Player.cpp)

target_link_libraries(sb_server ${Boost_LIBRARIES})
if (WIN32)
    target_link_libraries(sb_server wsock32)
    target_link_libraries(sb_server ws2_32)
endif ()