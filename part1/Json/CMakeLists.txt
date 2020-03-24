cmake_minimum_required(VERSION 3.10.2)
project(Json)

add_library(${PROJECT_NAME} src/jsonReader.cpp src/jsonWriter.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../GA/include
)