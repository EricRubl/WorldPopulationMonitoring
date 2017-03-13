cmake_minimum_required(VERSION 3.6)
project(WorldPopulationMonitoring)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c Domain/Country.h Domain/Country.c tests.h tests.c Domain/DynamicArray.h Domain/DynamicArray.c Repository/Repository.h Repository/Repository.c Controller/Controller.h Controller/Controller.c UI/console.h UI/console.c)
add_executable(WorldPopulationMonitoring ${SOURCE_FILES})