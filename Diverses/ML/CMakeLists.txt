cmake_minimum_required(VERSION 3.0.0)
project(ML VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_executable(
  ML main.cpp
  src/XYGraphDrawer.cpp
  src/KNNPoint.cpp
)

target_include_directories(ML PRIVATE include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# include(CPack)

