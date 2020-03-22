cmake_minimum_required(VERSION 3.10.2)
project(GA)

add_library(${PROJECT_NAME} src/individual.cpp src/helper.cpp)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)