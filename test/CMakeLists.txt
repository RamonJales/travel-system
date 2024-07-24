cmake_minimum_required(VERSION 3.8)

project(tests-project)

set(Sources
    test1.cpp
)

add_executable(tests-project ${Sources})

target_link_libraries(tests-project PUBLIC
    gtest_main
    travelSystemLib
)

add_test(NAME tests-project COMMAND tests-project)

