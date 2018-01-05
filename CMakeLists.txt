cmake_minimum_required(VERSION 3.8)
project(bachelor)

set(CMAKE_CXX_STANDARD 11)

set(LEDALIBINCLDIR "/home/benedikt/bachelor/LEDA-6.4/incl")


set(SOURCE_FILES main.cpp functions.h reduction.h)

add_executable(bachelor ${SOURCE_FILES} reduction.h)

include_directories(${LEDALIBINCLDIR})

target_link_libraries(bachelor leda X11 m)

target_compile_definitions(bachelor
        PUBLIC -DPROJECT_DIRECTORY="${CMAKE_SOURCE_DIR}")