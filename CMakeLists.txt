cmake_minimum_required(VERSION 3.10)
project(cookpateAdventOfCode)

if ( CMAKE_COMPILER_IS_GNUCC )
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wno-conversion -O0 -g -fsanitize=address -fno-omit-frame-pointer" )
endif()

add_executable(day1 day1-calorie-counting.cc helper.cc)
target_compile_features(day1 PUBLIC cxx_std_17)

add_executable(day1-part2 day1-calorie-counting-2.cc helper.cc)
target_compile_features(day1-part2 PUBLIC cxx_std_17)
