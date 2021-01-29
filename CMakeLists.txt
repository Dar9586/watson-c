cmake_minimum_required(VERSION 2.0)
project(watsonC C)

set(CMAKE_C_STANDARD 90)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-Fast")

add_subdirectory(src/lib)
add_executable(watsonC src/main.c)
target_link_libraries(watsonC LINK_PUBLIC cwatson)
