cmake_minimum_required(VERSION 3.10.2)
project(JsonReader)

add_library(${PROJECT_NAME} src/jsonReader.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../GA/include
)