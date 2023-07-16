cmake_minimum_required(VERSION 3.10.2)
project(tests)

set(GTest_DIR "../lib/share/gtest/")
find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} test_calculations.cpp)

target_link_libraries(
  ${PROJECT_NAME}
  calculations
  GTest::gmock 
  GTest::gtest 
  GTest::gmock_main
  GTest::gtest_main
)
