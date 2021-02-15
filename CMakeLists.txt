cmake_minimum_required(VERSION 3.17)
project(EmpireLegends)

set(CMAKE_CXX_STANDARD 17)

add_executable(EmpireLegends src/main.cpp "src/Map Loader/MapLoader.cpp" "src/Map Loader/MapLoader.h" "src/Map Loader/MapLoaderDriver.cpp")