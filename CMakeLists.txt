cmake_minimum_required(VERSION 3.17)
project(EmpireLegends)

set(CMAKE_CXX_STANDARD 17)

add_executable(EmpireLegends src/main.cpp src/Player/Player.cpp src/Player/Player.h src/Player/PlayerDriver.cpp src/BiddingFacility/BiddingFacility.cpp src/BiddingFacility/BiddingFacility.h src/BiddingFacility/BiddingFacilityDriver.cpp)
