cmake_minimum_required(VERSION 3.17)
project(EmpireLegends)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/Player/Player.cpp src/Player/Player.h src/A2_Part4_Driver.cpp src/BiddingFacility/BiddingFacility.cpp src/BiddingFacility/BiddingFacility.h src/BiddingFacility/BiddingFacilityDriver.cpp "src/Map Loader/MapLoader.cpp" "src/Map Loader/MapLoader.h" "src/Map Loader/MapLoaderDriver.cpp" "src/Cards/Cards.cpp" "src/Cards/Cards.h" "src/Cards/CardsDriver.cpp" "src/Map/Map.cpp" "src/Map/Map.h" "src/Map/MapDriver.cpp" src/Cards/Deck.cpp src/Cards/Deck.h src/Cards/Hand.cpp src/Cards/Hand.h src/A2_Part3_Driver.cpp src/A2_Part2_Driver.cpp src/A2_Part1_Driver.cpp src/A2_Part6_Driver.cpp src/Game/Game.cpp src/Game/Game.h src/A2_BiddingFacility_test.cpp src/A2_Part5_Driver.cpp src/Observer.h src/Subject.h src/Observer.cpp src/Subject.cpp)

add_executable(EmpireLegends ${SOURCE_FILES})