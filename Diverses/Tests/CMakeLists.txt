cmake_minimum_required(VERSION 3.10.2) 
project(Tests)

# include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(modules/calculations)
add_subdirectory(modules/calculations2)

add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
  ${PROJECT_NAME} 
  calculations
  calculations2
)
