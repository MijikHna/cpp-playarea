cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 20)

project(GraphAlgorithms VERSION 0.1.0)

# target_include_directories(${PROJECT_NAME} PRIVATE include/)
include_directories(${CMAKE_SOURCE_DIR}/include)

# target_link_libraries(GraphAlgorithms PRIVATE lib/)
# add_library(ncurses STATIC ./lib/)
# link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(
  GraphAlgorithms main.cpp
  src/Vertex.cpp
  src/VertexNeighbor.cpp
  src/VertexWithNeighbors.cpp
  src/VertexGraphDrawer.cpp
  src/PrismAlgorithm.cpp
)

# target_link_libraries(${PROJECT_NAME} ncurses)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
