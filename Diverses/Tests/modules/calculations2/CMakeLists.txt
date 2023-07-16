project(calculations2) 

add_library(calculations2 calculations2.cpp calculations2.hpp)

target_link_libraries(${PROJECT_NAME} calculations)
