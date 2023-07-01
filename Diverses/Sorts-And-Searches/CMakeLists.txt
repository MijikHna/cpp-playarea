cmake_minimum_required(VERSION 3.0.0)
project(SortsAndSearches VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
  SortsAndSearches main.cpp 
  src/BubbleSort.cpp
  src/BinarySearch.cpp
)

target_include_directories(SortsAndSearches PRIVATE include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
