cmake_minimum_required(VERSION 3.5)

project (studiousdollop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (studiousdollop ${source_files})

# Link SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(studiousdollop SQLite::SQLite3)

target_link_libraries(studiousdollop stdc++fs)
