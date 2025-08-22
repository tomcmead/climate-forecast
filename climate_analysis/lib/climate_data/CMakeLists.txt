cmake_minimum_required(VERSION 3.22.1)

set(LIB_NAME
    ClimateData
)

project(${LIB_NAME})

set(SRC_FILES
<<<<<<< HEAD
    src/climate_data.cpp
    src/climate_url.cpp)
=======
    src/climate_data.cpp)
>>>>>>> a9681a9be54f7cb9e4c9109da4e6e859cf65cd1a

add_library(${LIB_NAME} STATIC
    ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC
<<<<<<< HEAD
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/../../_deps/rapidjson-src/include)
=======
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
>>>>>>> a9681a9be54f7cb9e4c9109da4e6e859cf65cd1a

target_link_libraries(${LIB_NAME} PRIVATE 
    spdlog
    CurlHandler)