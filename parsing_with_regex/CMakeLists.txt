
cmake_minimum_required(VERSION 3.0)

project(zgml_handler LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CXX_SOURCES "src/*.cpp")

include_directories(inc)
        
add_executable(${CMAKE_PROJECT_NAME}
               main.cpp ${CXX_SOURCES})

