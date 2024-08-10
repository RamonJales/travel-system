cmake_minimum_required(VERSION 3.8)

project(travel-system C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)

#Defining a library to use in test directory
set(Headers
    src/include/City.hpp
    src/include/Passenger.hpp
    src/include/interface.hpp
    src/include/Route.hpp
    src/include/enums/RouteTypeEnum.hpp
    src/include/enums/TransportTypeEnum.hpp
    src/include/Transport.hpp
    src/include/Trip.hpp
    src/include/Controller.hpp
    src/include/repositories/repositoryCity.hpp
    src/include/repositories/repositoryTransport.hpp
    src/include/repositories/repositoryPassenger.hpp
    src/include/repositories/repositoryTrip.hpp
    sqlite3/sqlite3.h
    src/include/CityGraph.hpp
)
set(Sources
    src/impl/City.cpp
    src/impl/Passenger.cpp
    src/impl/interface.cpp
    src/impl/Route.cpp
    src/impl/Transport.cpp
    src/impl/Trip.cpp
    src/impl/Controller.cpp
    src/impl/repositories/repositoryCity.cpp
    src/impl/repositories/repositoryTransport.cpp
    src/impl/repositories/repositoryPassenger.cpp
    src/impl/repositories/repositoryTrip.cpp
    sqlite3/sqlite3.c
    src/impl/CityGraph.cpp
)
add_library(travelSystemLib STATIC ${Sources} ${Headers})

add_executable(project 
  src/main.cpp
)

# Adicione o diretório do SQLite
add_library(sqlite3 sqlite3/sqlite3.c)

# Adicione a biblioteca sqlite3
target_include_directories(sqlite3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3)

target_include_directories(project PRIVATE src/include)
target_link_libraries(project PRIVATE travelSystemLib sqlite3)
