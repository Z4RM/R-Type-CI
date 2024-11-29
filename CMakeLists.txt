cmake_minimum_required(VERSION 3.29)
project(R_Type VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(spdlog REQUIRED)

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
