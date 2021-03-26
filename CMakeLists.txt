cmake_minimum_required(VERSION 3.17)
project(EmpireLegends)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/Player/Player.cpp src/Player/Player.h src/Player/PlayerDriver.cpp src/BiddingFacility/BiddingFacility.cpp src/BiddingFacility/BiddingFacility.h src/BiddingFacility/BiddingFacilityDriver.cpp "src/Map Loader/MapLoader.cpp" "src/Map Loader/MapLoader.h" "src/Map Loader/MapLoaderDriver.cpp" "src/Cards/Cards.cpp" "src/Cards/Cards.h" "src/Cards/CardsDriver.cpp" "src/Map/Map.cpp" "src/Map/Map.h" "src/Map/MapDriver.cpp" src/Cards/Deck.cpp src/Cards/Deck.h src/Cards/Hand.cpp src/Cards/Hand.h src/Cards/DemoPart2.cpp)

add_executable(EmpireLegends ${SOURCE_FILES})