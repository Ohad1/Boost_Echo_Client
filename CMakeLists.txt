cmake_minimum_required(VERSION 3.13)
project(Boost_Echo_Client)
set(BOOST_ROOT "/path_to_boost_1_57_0")

find_package(Boost 1.57.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(Boost_Echo_Client
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp
        makefile src/ReadFromSocket.cpp src/ReadFromKeyboard.cpp)
