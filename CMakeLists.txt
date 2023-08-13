cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(math_analyzer LANGUAGES CXX)

find_package(Curses REQUIRED)

if(Curses_FOUND)
    message("\"ncurses\" lib found!")
else()
    message(FATAL_ERROR "Cannot find \"ncurses\" lib!")
endif()

add_subdirectory(src)
