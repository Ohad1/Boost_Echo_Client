cmake_minimum_required(VERSION 3.13)
project(Boost_Echo_Client)
set(BOOST_ROOT "/path_to_boost_1_57_0")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
SET(PLATFORM_SPECIFIC_LIBS "-lpthread")

find_package(Boost 1.57.0 COMPONENTS filesystem regex)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Boost_Echo_Client
            include/connectionHandler.h
            src/connectionHandler.cpp
            src/echoClient.cpp
            makefile src/ReadFromSocket.cpp src/ReadFromKeyboard.cpp)
    target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})
endif()
set(CMAKE_CXX_STANDARD 11)
target_compile_features(Boost_Echo_Client PUBLIC cxx_std_11)
include_directories(.)
include_directories(include)
include_directories(src)
target_link_libraries(Boost_Echo_Client -lpthread)


