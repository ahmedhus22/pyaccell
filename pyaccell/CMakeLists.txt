add_library(
    pyaccell
    shader.hpp
    shader.cpp
)

set_target_properties(pyaccell PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pyaccell PRIVATE glfw glad)
target_include_directories(pyaccell PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
