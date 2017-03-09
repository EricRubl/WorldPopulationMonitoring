cmake_minimum_required(VERSION 3.6)
project(WorldPopulationMonitoring)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c Domain/Country.h Domain/Country.c tests.h tests.c Domain/DynamicArray.h)
add_executable(WorldPopulationMonitoring ${SOURCE_FILES})