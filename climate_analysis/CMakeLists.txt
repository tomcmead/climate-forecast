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

set(SRC
    ${SRC_DIR}/climate_analysis.cpp
)
set(LIBS
)

set(TEST_NAME
    TestClimateAnalysis
)

################################
# Project
################################
project(${PROJECT_NAME})

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