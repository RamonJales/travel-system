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
    src/include/Passenger.hpp
    src/include/Route.hpp
    src/include/enums/RouteTypeEnum.hpp
)
set(Sources
    src/impl/City.cpp
    src/impl/Passenger.cpp
    src/impl/interface.cpp
    src/impl/Passenger.cpp
    src/impl/Route.cpp
)
add_library(travelSystemLib STATIC ${Sources} ${Headers})

add_executable(project 
  src/main.cpp
)

target_include_directories(project PRIVATE src/include)
target_link_libraries(project PRIVATE travelSystemLib)

