project(Frostpunk LANGUAGES CXX)
set(CMAKE_CXX_COMPILER g++)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(a.out main.cpp FrostPunk.cpp FrostPunk.hpp)
add_executable(test.out tests.cpp FrostPunk.cpp FrostPunk.hpp)
