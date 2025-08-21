cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME
    ClimateAnalysis
)

set(SRC_DIR
    src
)
set(LIB_DIR
    lib
)
set(TEST_DIR
    test
)
set(DOC_DIR
    docs
)

set(SRC
    ${SRC_DIR}/climate_analysis.cpp
)
set(LIBS
)

set(TEST_NAME
    TestClimateAnalysis
)

option(BUILD_DOCS "Build documentation" OFF)

################################
# Project
################################
project(${PROJECT_NAME})

if(BUILD_DOCS)
    add_subdirectory(${DOC_DIR})
endif()

add_subdirectory(${LIB_DIR})
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

################################
# Tests
################################
# project(${TEST_NAME})

# enable_testing()

# add_executable(
#     ${TEST_NAME}
# )
# target_include_directories(${TEST_NAME} PUBLIC
# )
# target_link_libraries(
#     ${TEST_NAME}
#     PRIVATE
#     ${LIBS}
#     GTest::gtest_main
# )