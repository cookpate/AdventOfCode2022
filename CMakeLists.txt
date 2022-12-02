cmake_minimum_required(VERSION 3.24)
project(cookpateAdventOfCode)

add_executable(day1 day1-calorie-counting.cc helper.cc)
target_compile_features(day1 PUBLIC cxx_std_17)
set_target_properties(day1 PROPERTIES CXX_EXTENSIONS OFF)

add_executable(day1-part2 day1-calorie-counting-2.cc helper.cc)
target_compile_features(day1-part2 PUBLIC cxx_std_17)
set_target_properties(day1-part2 PROPERTIES CXX_EXTENSIONS OFF)
