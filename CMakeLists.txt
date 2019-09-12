cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

project(number_recognition)

include_directories(./include ./source)

add_library(matrix	./source/matrix.cpp)
add_library(nnw	./source/nnw.cpp)
add_library(observer	./source/observer.cpp)

target_link_libraries(nnw matrix)
target_link_libraries(observer nnw)
target_link_libraries(observer ${OpenCV_LIBS})

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    set(EXE_NAME exe)
    add_executable(${EXE_NAME} main.cpp)
    target_link_libraries(${EXE_NAME} observer)

ELSEIF(CMAKE_BUILD_TYPE MATCHES Test)
    message("Test build.")
    set(EXE_NAME tester)
    add_executable(${EXE_NAME} tests/representation/C++/testing.cpp)
    target_link_libraries(${EXE_NAME} observer)

ELSEIF(CMAKE_BUILD_TYPE MATCHES Generate)
    message("Generate build.")
    set(EXE_NAME generator)
    add_executable(${EXE_NAME} tests/representation/C++/data_generator.cpp)
    target_link_libraries(${EXE_NAME} observer)

ENDIF()
