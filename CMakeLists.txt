cmake_minimum_required(VERSION 3.10)
project(cookpateAdventOfCode)

set(CMAKE_CXX_STANDARD 17)

if ( CMAKE_COMPILER_IS_GNUCC )
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wno-conversion -O0 -g -fsanitize=address -fno-omit-frame-pointer" )
endif()

add_library( helper STATIC helper.cc )
target_compile_features( helper PUBLIC cxx_std_17 )

function( add_challenge_solution CHALLENGE_TARGET CHALLENGE_SOURCE )
    add_executable( ${CHALLENGE_TARGET} ${CHALLENGE_SOURCE} )
    target_compile_features( ${CHALLENGE_TARGET} PUBLIC cxx_std_17 )
    target_link_libraries( ${CHALLENGE_TARGET} helper )
endfunction()

add_challenge_solution( day1 day1-calorie-counting.cc )
add_challenge_solution( day1-part2 day1-calorie-counting-2.cc )
add_challenge_solution( day2 day2-rock-paper-scissors.cc )
add_challenge_solution( day2-part2 day2-rock-paper-scissors-2.cc )
add_challenge_solution( day3 day3-rucksack.cc )
add_challenge_solution( day3-part2 day3-rucksack-2.cc )
add_challenge_solution( day4 day4-camp-cleanup.cc )
add_challenge_solution( day5 day5-supply-stacks.cc )
